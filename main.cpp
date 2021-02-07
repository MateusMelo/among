//
// Created by m2 on 2/2/21.
//

#include <glibmm.h>
#include <gtkmm/application.h>

#include "src/gui/MainWindow.h"

int main(int argc, char *argv[]) {
    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");
    MainWindow main_window;
    return app->run(main_window);
}
