#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <QTableWidget>


class TableWidget : public QTableWidget
{
public:
    TableWidget(QWidget* parent = nullptr);

    QMap<int,QString> getRowValues();
    void setRowValues(QMap<QString,QString> values);

private:
    QMap<int,QString> m_values;
    QStringList m_headerNames;

public slots:
    void slotSetHeaderNames(QStringList headerNames);
    void slotCellChanged(int row, int column);


};

#endif // TABLEWIDGET_H
