#include "PushButtonRecordEdit.h"

PushButtonRecordEdit::PushButtonRecordEdit(QWidget* parent) : QPushButton (parent)
{
    connect(this, &PushButtonRecordEdit::clicked, this,&PushButtonRecordEdit::slotSendConfirmationSignal);
}

void PushButtonRecordEdit::slotSetDisabled()
{
    setEnabled(false);
}
void PushButtonRecordEdit::slotSetEnabled()
{
    setEnabled(true);
}

void PushButtonRecordEdit::slotSetMode(PushButtonMode mode)
{
    if (mode == PushButtonMode::addMode)
    {
        slotSetModeToAddMode();
    }
    else if (mode == PushButtonMode::editMode)
    {
        slotSetModeToEditMode();
    }
    // With change in mode, initially we disable the button:
    setEnabled(false);
}

void PushButtonRecordEdit::slotSetModeToEditMode()
{
    m_mode = PushButtonMode::editMode;
    setText(ButtonTextEditMode);
}
void PushButtonRecordEdit::slotSetModeToAddMode()
{
    m_mode = PushButtonMode::addMode;
    setText(ButtonTextAddMode);
}

void PushButtonRecordEdit::slotSendConfirmationSignal()
{
    if (m_mode == PushButtonMode::addMode)
    {
        emit signalConfirmInsert();
    }
    else if (m_mode == PushButtonMode::editMode)
    {
        emit signalConfirmEdit();
    }
}


