#ifndef COMBOBOXCOSTENTRY_H
#define COMBOBOXCOSTENTRY_H

#include <QComboBox>


class ComboBoxCostEntry : public QComboBox
{
    Q_OBJECT
public:
    ComboBoxCostEntry(QWidget* parent = nullptr);

    void setItems(QMap<int,QString> items);
    QMap<int,QString> getItems();

    QString getCurrentItem();

private:
    QMap<int,QString> m_items;
};

#endif // COMBOBOXCOSTENTRY_H
