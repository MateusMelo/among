//
// Created by m2 on 2/2/21.
//

#ifndef AMONG_MAINWINDOW_H
#define AMONG_MAINWINDOW_H

#include <gtkmm/button.h>
#include <gtkmm/window.h>

class MainWindow : public Gtk::Window {
    public:
        MainWindow();

        void on_app_activate();
};

#endif //AMONG_MAINWINDOW_H
