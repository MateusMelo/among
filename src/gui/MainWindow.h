//
// Created by m2 on 2/2/21.
//

#ifndef AMONG_MAINWINDOW_H
#define AMONG_MAINWINDOW_H

#include <gtkmm.h>
#include <mongocxx/client.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/instance.hpp>

#include "ModelColumn.h"

class MainWindow : public Gtk::Window {
    ModelColumn model_column;

    Gtk::VBox v_box;

    Gtk::ScrolledWindow scrolled_window;
    Gtk::TreeView tree_view;
    Glib::RefPtr<Gtk::TreeStore> ref_tree_store;

    mongocxx::instance instance{};
    mongocxx::uri uri;
    mongocxx::client client;

    protected:
        void on_treeview_row_activated(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* column);

    public:
        MainWindow();
};

#endif //AMONG_MAINWINDOW_H
