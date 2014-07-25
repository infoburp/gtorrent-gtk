#pragma once

#include <gtorrent/Torrent.hpp>

#include <gtkmm/box.h>
#include <gtkmm/notebook.h>
#include <gtkmm/label.h>

#include <Application.hpp>

#include "GtkBlockBar.hpp"
#include "GtkGraph.hpp"

class GtkTorrentInfoBar : public Gtk::Box
{
private:
	GtkBlockBar *m_progress;
	Gtk::Label *m_title;
	GtkGraph *m_graph;
	Gtk::Notebook *m_notebook;
public:
	GtkTorrentInfoBar();
	void updateInfo(shared_ptr<gt::Torrent> selected);
};
