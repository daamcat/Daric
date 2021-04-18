#ifndef MYSQLTABLEMODEL_H
#define MYSQLTABLEMODEL_H

/*
Refs:
https://doc.qt.io/qt-5/qtquick-modelviewsdata-cppmodels.html#changing-model-data
https://wiki.qt.io/QML_and_QSqlTableModel
*/

#include <QSqlTableModel>
#include <QHash>

class QSqlDatabase;

class MySqlTableModel : public QSqlTableModel
{
    Q_OBJECT

public:
    explicit MySqlTableModel(QObject *parent = nullptr, QSqlDatabase db = QSqlDatabase());
    ~MySqlTableModel() override;

    virtual QHash<int, QByteArray> roleNames() const override;
    // "const": roleNames() is a "constant member function" it is not allowed to modify the object. For example,
    // we can't set a new value for a variable member inside this constant member function. Try and you will
    // get compiler error!
    // "override": roleName() was a virtual function in base class and it is overwritten in here.
    // "virtual": Keyword for virtual function in base class. It is not necessary to use this keyword in derived
    // class function declaration. But using it with "override" together ensures that both function declarations
    // are the same. For example, if the type of input argument in derived class is different than the base class,
    // using "virtual" keyword in derived class will notify us this difference with causeing compilation error.


    QVariant data(const QModelIndex &index,
                  int role = Qt::ItemDataRole::DisplayRole) const override;

    // rowCount has been reimplemented in QSqlTableModel:
    // virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

private:
    QVector<QVariant> m_data;

};

#endif // MYSQLTABLEMODEL_H
