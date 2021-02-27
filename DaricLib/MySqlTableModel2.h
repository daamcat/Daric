#ifndef MYSQLTABLEMODEL2_H
#define MYSQLTABLEMODEL2_H

#include <QSqlRelationalTableModel>

// I very likely need to consider inheritting from class QSqlRelationalTableModel.
// Inheritting from QSqlRelationalTableModel enables me to benefit foreign key support.

class MySqlTableModel2 : public QSqlRelationalTableModel
{
public:
    MySqlTableModel2(QObject *parent = nullptr, QSqlDatabase db = QSqlDatabase());
};

#endif // MYSQLTABLEMODEL2_H
