//
// Created by m2 on 2/2/21.
//

#include <iostream>

#include <glibmm.h>
#include "gtkmm/builder.h"

#include "MainWindow.h"
#include "UiRegistry.h"

MainWindow::MainWindow() {
    Gtk::Dialog *dialog;
    auto builder = Gtk::Builder::create();
    try {
        builder->add_from_string(UiRegistry::getUString());
    } catch (const Glib::FileError& error) {
        std::cerr << "FileError: " << error.what() << std::endl;
        return;
    } catch (const Glib::MarkupError& error) {
        std::cerr << "MarkupError: " << error.what() << std::endl;
        return;
    } catch (const Gtk::BuilderError& error) {
        std::cerr << "BuilderError: " << error.what() << std::endl;
        return;
    }

    builder->get_widget<Gtk::Dialog>("dialog", dialog);

    add(*dialog);
    show_all();
}