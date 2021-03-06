#include "GtkMainWindow.hpp"
#include <future>
#include <gtorrent/Platform.hpp>
#include <gtorrent/Settings.hpp>

#include <boost/algorithm/string.hpp>
#include <giomm.h>
#include <glibmm.h>
#include <libnotify/notify.h>

#include <gtkmm/filechooserdialog.h>
#include <gtkmm/hvseparator.h>
#include <gtkmm/main.h>
#include <gtkmm/paned.h>
#include <gtkmm/scrollbar.h>
#include <gtkmm.h>
#include <gtkmm/stock.h>

#include "../Application.hpp"
#include "GtkAssociationDialog.hpp"
#include "GtkTorrentTreeView.hpp"
#include "GtkTorrentInfoBar.hpp"
#include "GtkSettingsDialog.hpp"
#include "GtkTorrentSideBar.hpp"

// TODO: GtkRevealer should contain a listbox, list view of even a tree view like nautilus's
//       so remove the header, cutomize the cells, and enable the revealer with the property button
//       Also find a way to darken the treeview when the sidebar is shown, the same way the window is
//       darkened when a modal dialog is opened.


/**
* Sets up the main window.
*/
GtkMainWindow::GtkMainWindow(GtkWindow *win, const Glib::RefPtr<Gtk::Builder> rbuilder) : Gtk::Window(win), builder(rbuilder), m_core(Application::getSingleton()->getCore())
{
	notify_init ("gTorrent");

	GtkTorrentSideBar *sidebar;
	Gtk::Revealer *revealer;

	builder->get_widget(  "addTorrentButton", addTorrentButton);
	builder->get_widget(  "addTorrentButton", addTorrentButton);
	builder->get_widget(   "addMagnetButton",  addMagnetButton);
	builder->get_widget(      "resumeButton",     resumeButton);
	builder->get_widget(       "pauseButton",      pauseButton);
	builder->get_widget(      "deleteButton",     removeButton);
	//builder->get_widget( "preferencesButton", propertiesButton);
	builder->get_widget(    "settingsButton",   settingsButton);
	builder->get_widget(             "panel",            panel);
	builder->get_widget(    "scrolledWindow",   scrolledWindow);
	builder->get_widget(           "vSepOne",    vSeparatorOne);
	builder->get_widget(           "vSepTwo",    vSeparatorTwo);
	builder->get_widget(        "sidebarRev",         revealer);
	builder->get_widget_derived(   "infobar",        m_infobar);
	builder->get_widget_derived(  "treeview",       m_treeview);
	builder->get_widget_derived(   "sidebar",          sidebar);

	panel->pack2(*m_infobar);

	// Apparently can't use lambdas on these two unless doing something awful
	Glib::signal_timeout().connect_seconds(sigc::mem_fun(*this, &GtkMainWindow::onSecTick), 1);
	signal_delete_event().connect(sigc::mem_fun(*this, &GtkMainWindow::onDestroy));

	addTorrentButton->signal_clicked().connect([this](){        onAddBtnClicked();});
	pauseButton     ->signal_clicked().connect([this](){      onPauseBtnClicked();});
	resumeButton    ->signal_clicked().connect([this](){     onResumeBtnClicked();});
	removeButton    ->signal_clicked().connect([this](){     onRemoveBtnClicked();});
	settingsButton  ->signal_clicked().connect([this](){   onSettingsBtnClicked();});
	addMagnetButton ->signal_clicked().connect([this](){  onAddMagnetBtnClicked();});
	//propertiesButton->signal_clicked().connect([revealer](){ revealer->set_reveal_child(!revealer->get_reveal_child());});

	magEntry   = Gtk::manage(new Gtk::Entry());
	revealer->set_reveal_child(true);
	magEntry->set_visible();
	magEntry->set_width_chars(75);
	magPopover = Gtk::manage(new Gtk::Popover());

	magPopover->add(*magEntry);
	magPopover->set_relative_to(*addMagnetButton);
	addMagnetButton->set_popover(*magPopover);
	magPopover->set_position(Gtk::POS_LEFT);
	
	sidebar_scrolledwindow->set_min_content_width(150);

	for(auto tor : Application::getSingleton()->getCore()->getTorrents())
	{
		tor->onStateChanged = [this](int oldstate, std::shared_ptr<gt::Torrent> t){ torrentStateChangedCallback(oldstate, t); };
		m_treeview->addCell(tor);
	}

	if (gt::Settings::settings["FileAssociation"] == "" ||
		gt::Settings::settings["FileAssociation"] == "-1")
	{
		GtkAssociationDialog *dialog = 0;
		builder->get_widget_derived("fileAssociationDialog", dialog);
		dialog->set_transient_for(*this);
		dialog->set_default_response(1);
		int code = dialog->run();
		if(code != -1)
			gt::Platform::associate(dialog->aWithMagnets, dialog->aWithTorrents);
		gt::Settings::settings["FileAssociation"] = std::to_string(code);
		delete dialog;
	}

	d = new GtkSettingsDialog(this);
}

/**
* Does something each second.
*/
bool GtkMainWindow::onSecTick()
{
	m_treeview->updateCells();
	m_infobar->updateState(m_treeview->getFirstSelected());
	std::shared_ptr<gt::Torrent> t = m_core->update();
	if (t)
	{
		t->onStateChanged = [this](int oldstate, std::shared_ptr<gt::Torrent> t){ torrentStateChangedCallback(oldstate, t); };
		m_treeview->addCell(t);
	}
	scrolledWindow->get_vscrollbar()->set_child_visible(false);
	return true;
}

/**
* Does something when the add button is clicked.
*/
void GtkMainWindow::onAddBtnClicked()
{
	Gtk::FileChooserDialog fc("Browse for torrent file", Gtk::FILE_CHOOSER_ACTION_OPEN);
	fc.set_default_size(256, 256);
	fc.set_select_multiple();
	fc.set_transient_for(*this);
	fc.set_position(Gtk::WIN_POS_CENTER_ON_PARENT);
	fc.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
	fc.add_button("Select", Gtk::RESPONSE_OK);

	Glib::RefPtr<Gtk::FileFilter> filter_t = Gtk::FileFilter::create();
	filter_t->set_name("Torrent Files");
	filter_t->add_mime_type("application/x-bittorrent");
	fc.add_filter(filter_t);

	int result = fc.run();

	switch (result)
	{
	case Gtk::RESPONSE_OK:
		for (auto & f : fc.get_filenames())
		{
			std::shared_ptr<gt::Torrent> t = m_core->addTorrent(f);
			if (t)//Checks if t is not null
			{
				t->onStateChanged = [this](int oldstate, std::shared_ptr<gt::Torrent> t){ torrentStateChangedCallback(oldstate, t); };
				m_treeview->addCell(t);
			}
			//TODO Add error dialogue if torrent add is unsuccessful
		}
		break;
	}
}

void GtkMainWindow::torrentStateChangedCallback(int oldstate, std::shared_ptr<gt::Torrent> t)
{
	NotifyNotification *Hello = nullptr;

	int newstate = t->status().state;

	if(newstate == libtorrent::torrent_status::seeding && oldstate == libtorrent::torrent_status::downloading)
		Hello = notify_notification_new (t->status().name.c_str(), std::string(t->status().name + " has finished downloading.").c_str(), "dialog-information");
	else if(newstate == libtorrent::torrent_status::downloading  &&
			oldstate == libtorrent::torrent_status::downloading_metadata)
		Hello = notify_notification_new (t->status().name.c_str(), std::string(t->status().name + " has started downloading.").c_str(), "dialog-information");
	else
		return; //:^)

	notify_notification_show (Hello, NULL);
	g_object_unref(G_OBJECT(Hello));
}

/**
* Does something when the add magnet button is clicked.
*/
void GtkMainWindow::onAddMagnetBtnClicked()
{
	if(magPopover->get_visible())
	{
		Glib::RefPtr<Gtk::Clipboard> clip = Gtk::Clipboard::get();
		std::string link = clip->wait_for_text();
		if(gt::Core::isLink(link))
			magEntry->set_text(link);
	}
	else
	{
		std::shared_ptr<gt::Torrent> t = m_core->addTorrent(magEntry->get_text());
		if (t)
		{
			t->onStateChanged = std::bind(&GtkMainWindow::torrentStateChangedCallback, this, std::placeholders::_1, std::placeholders::_2);
			m_treeview->addCell(t);
		}
		magEntry->set_text("");
	}
}

/**
* Does something when the pause button is clicked.
*/
void GtkMainWindow::onPauseBtnClicked()
{
	m_treeview->setSelectedPaused(true);
	m_treeview->onSelectionChanged();
}

/**
* Does something when the resume button is clicked.
*/
void GtkMainWindow::onResumeBtnClicked()
{
	m_treeview->setSelectedPaused(false);
	m_treeview->onSelectionChanged();
}

/**
* Does something when the remove button is clicked.
*/
void GtkMainWindow::onRemoveBtnClicked()
{
	for(auto t : m_treeview->selectedTorrents())
		m_infobar->removeInfo(t);
	m_treeview->removeSelected();
}

/**
* Does something when the properties button is clicked.
*/
void GtkMainWindow::onPropertiesBtnClicked()
{

}

/**
* Does something when the window is destroyed. // That's some 10/10 doc right there.
*/
bool GtkMainWindow::onDestroy(GdkEventAny *event)
{
	m_treeview->saveColumns();
	notify_uninit();
	return false;
}

void GtkMainWindow::onSettingsBtnClicked()
{
	d->run();
}
