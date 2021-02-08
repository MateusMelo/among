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

MainWindow::MainWindow() :
v_box(Gtk::Orientation::ORIENTATION_VERTICAL),
uri("mongodb://localhost:27017"),
client(uri) {
    set_title("among");
    set_border_width(5);
    set_default_size(800, 600);

    add(v_box);

    scrolled_window.add(tree_view);

    scrolled_window.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);

    v_box.pack_start(scrolled_window);

    ref_tree_store = Gtk::TreeStore::create(model_column);
    tree_view.set_model(ref_tree_store);

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

    tree_view.signal_row_activated().connect(sigc::mem_fun(*this,
                                                            &MainWindow::on_treeview_row_activated) );


}

void MainWindow::on_treeview_row_activated(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn*) {
    const auto iter = ref_tree_store->get_iter(path);
    if(iter) {
        const auto row = *iter;

        std::string db_name = row.parent()->get_value(model_column.m_col_name);
        std::string coll_name = row.get_value(model_column.m_col_name);

        mongocxx::database db = client.database(db_name);
        mongocxx::collection coll = db.collection(coll_name);
        mongocxx::cursor cursor = coll.find({});
        for(auto doc : cursor) {
            std::cout << bsoncxx::to_json(doc) << "\n";
        }
    }
}
