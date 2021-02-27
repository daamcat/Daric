#include "MySqlTableModel2.h"

// I very likely need to consider inheritting from class QSqlRelationalTableModel.

MySqlTableModel2::MySqlTableModel2(QObject *parent, QSqlDatabase db) : QSqlRelationalTableModel (parent,db)
{
    setEditStrategy(EditStrategy::OnManualSubmit);

}
