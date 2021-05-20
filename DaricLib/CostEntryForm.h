#ifndef COSTENTRYFORM_H
#define COSTENTRYFORM_H

#include <QWidget>
#include <QMap>

class DatabaseManager;
class MySqlTableModel2;


namespace Ui {
class CostEntryForm;
}

class CostEntryForm : public QWidget
{
    Q_OBJECT

public:
    explicit CostEntryForm(QWidget *parent = nullptr);
    ~CostEntryForm();

    void setSqlTableModel(MySqlTableModel2* tableModel);


private:
    void insertRecord();

    Ui::CostEntryForm *ui;

    QMap<int,QString> m_tags;
    QMap<int,QString> m_shoppingSources;
    QMap<int,QString> m_paymentMeans;
    QMap<int,QString> m_currencies;

    MySqlTableModel2* m_tableModel;


protected:
    void mousePressEvent(QMouseEvent* event) override;
    //void showEvent(QShowEvent* event) override;

};

#endif // COSTENTRYFORM_H
