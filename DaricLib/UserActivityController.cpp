#include "UserActivityController.h"

#include "TableView.h"
#include "TableWidget.h"
#include "PushButtonRecordEdit.h"
#include <QComboBox>
#include <QObject>
#include <QItemSelectionModel>

UserActivityController::UserActivityController(TableView* dataTable,
                                               TableWidget* editTable,
                                               PushButtonRecordEdit* pushButton,
                                               QComboBox* comboboxSelectTable) :
    m_dataTable(dataTable),
    m_editTable(editTable),
    m_pushButton(pushButton),
    m_comboboxSelectTable(comboboxSelectTable)
{
    QObject::connect(m_comboboxSelectTable, &QComboBox::currentTextChanged,
                     m_pushButton, &PushButtonRecordEdit::slotSetDisabled);
    QObject::connect(m_editTable, &TableWidget::cellChanged,
                     m_pushButton, &PushButtonRecordEdit::slotSetEnabled);
    QObject::connect(m_dataTable,&TableView::signalEditRecord,
                     m_pushButton, &PushButtonRecordEdit::slotSetModeToEditMode);
    if (m_dataTable->selectionModel())
    {
        QObject::connect(m_dataTable->selectionModel(), &QItemSelectionModel::selectionChanged,
                         m_pushButton, &PushButtonRecordEdit::slotSetModeToAddMode);
    }
}
