#pragma once

#include <gtorrent/Core.hpp>
#include <gtkmm/builder.h>
#include <gtkmm/button.h>
#include <gtkmm/entry.h>
#include <gtkmm/headerbar.h>
#include <gtkmm/menubutton.h>
#include <gtkmm/popover.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/window.h>
#include <gtkmm/separator.h>
#include <gtkmm/paned.h>

class GtkTorrentInfoBar;
class GtkTorrentTreeView;
class GtkSettingsDialog;

class GtkMainWindow : public Gtk::Window
{
	const Glib::RefPtr<Gtk::Builder> builder;
	std::shared_ptr<gt::Core> &m_core;
	GtkSettingsDialog *d = nullptr;

	// Signal Responders

	bool onKeyPress(GdkEventKey *event);
	void onAboutBtnClicked();
	void onAddBtnClicked();
	void onAddMagnetBtnClicked();
	void onPauseBtnClicked();
	void onResumeBtnClicked();
	void onRemoveBtnClicked();
	void onSettingsBtnClicked();
	void onPropertiesBtnClicked();
	void onFileDropped(const Glib::RefPtr<Gdk::DragContext>& context, int x, int y, const Gtk::SelectionData& selection_data, guint info, guint time);

public:
	void torrentStateChangedCallback(int oldstate, std::shared_ptr<gt::Torrent> t);

	GtkTorrentTreeView *m_treeview = nullptr;
	GtkTorrentInfoBar  *m_infobar  = nullptr;

	Gtk::Button         *addTorrentButton       = nullptr;
	Gtk::Button         *resumeButton           = nullptr;
	Gtk::Button         *pauseButton            = nullptr;
	Gtk::Button         *removeButton           = nullptr;
	Gtk::Button         *propertiesButton       = nullptr;
	Gtk::Button         *settingsButton         = nullptr;
	Gtk::Separator      *vSeparatorOne          = nullptr;
	Gtk::Separator      *vSeparatorTwo          = nullptr; 
	Gtk::Popover        *magPopover             = nullptr;
	Gtk::Entry          *magEntry               = nullptr;
	Gtk::ScrolledWindow *scrolledWindow         = nullptr; // Whichever chucklefuck made this member, get the right name.
	Gtk::ScrolledWindow *sidebar_scrolledwindow = nullptr;
	Gtk::MenuButton     *addMagnetButton        = nullptr;
	Gtk::Paned          *panel                  = nullptr; // Whichever chucklefuck made this member, get the right name.

	GtkMainWindow(GtkWindow*, const Glib::RefPtr<Gtk::Builder>);
	bool onDestroy(GdkEventAny *event);
	bool onSecTick();
};
