//
// Created by m2 on 2/6/21.
//

#ifndef AMONG_MODELCOLUMN_H
#define AMONG_MODELCOLUMN_H

#include <gtkmm.h>

class ModelColumn : public Gtk::TreeModel::ColumnRecord {
public:
    ModelColumn();

    Gtk::TreeModelColumn<std::string> m_col_name;
};

#endif //AMONG_MODELCOLUMN_H
