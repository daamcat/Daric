#ifndef MYSQLTABLEMODEL2_H
#define MYSQLTABLEMODEL2_H

#include <QSqlRelationalTableModel>

// I very likely need to consider inheritting from class QSqlRelationalTableModel.
// Inheritting from QSqlRelationalTableModel enables me to benefit foreign key support.

class MySqlTableModel2 : public QSqlRelationalTableModel
{
public:
    MySqlTableModel2(QObject *parent = nullptr, QSqlDatabase db = QSqlDatabase());

    // In reimplementation of headerData() it is important to check the input role and to return proper header
    // only for display role. I still don't know why, but without this check, headerData will not be set properly.
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    bool select() override;

    QStringList getHeaderNames();
    QStringList getRoleNames();

    bool addRecord(const int& row, QMap<int , QString> values);
    bool setRecord(const int& row, QMap<int , QString> values);
    QSqlRecord getRecord(const int& row);
    QMap<QString , QString> getRow(const int& row);

public slots:
    bool slotRemoveRecord(int row);


private:
    QStringList m_headerNames;
    QStringList m_roleNames;


};

#endif // MYSQLTABLEMODEL2_H
