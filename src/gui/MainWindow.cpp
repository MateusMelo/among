//
// Created by m2 on 2/2/21.
//

#include <cstdint>
#include <iostream>
#include <vector>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/instance.hpp>
#include <bsoncxx/builder/stream/helpers.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/builder/stream/array.hpp>

#include "gtkmm/builder.h"

#include "MainWindow.h"

using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::open_document;

MainWindow::MainWindow() : v_box(Gtk::Orientation::ORIENTATION_VERTICAL) {
    set_title("among");
    set_border_width(5);
    set_default_size(800, 600);

    add(v_box);

    scrolled_window.add(tree_view);

    scrolled_window.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);

    v_box.pack_start(scrolled_window);

    ref_tree_store = Gtk::TreeStore::create(model_column);
    tree_view.set_model(ref_tree_store);

    mongocxx::instance instance{};
    mongocxx::uri uri("mongodb://localhost:27017");
    mongocxx::client client(uri);
    mongocxx::database db = client["among"];
    mongocxx::collection coll = db["among_c"];

    for (auto const& db_name: client.list_database_names()) {
        Gtk::TreeModel::Row row = *(ref_tree_store->append());
        row[model_column.m_col_name] = db_name;

        mongocxx::database c_db = client[db_name];
        for (auto const& coll_name: c_db.list_collection_names()) {
            Gtk::TreeModel::Row child_row = *(ref_tree_store->append(row.children()));
            child_row[model_column.m_col_name] = coll_name;
        }
    }

    tree_view.append_column("Databases", model_column.m_col_name);

    show_all_children();
}