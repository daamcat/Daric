#include "ComboBoxCostEntry.h"

ComboBoxCostEntry::ComboBoxCostEntry(QWidget* parent) : QComboBox (parent)
{

}

void ComboBoxCostEntry::setItems(QMap<int,QString> items)
{
    m_items = items;
    this->clear();
    this->addItem("");
    for (QString e : m_items.values())
    {
        this->addItem(e);
    }
}

QMap<int,QString> ComboBoxCostEntry::getItems()
{
    return m_items;
}

QString ComboBoxCostEntry::getCurrentItem()
{
    if (!this->currentText().isEmpty())
    {
        return QString::number(m_items.key(this->currentText()));
    }
    return QString();
}
