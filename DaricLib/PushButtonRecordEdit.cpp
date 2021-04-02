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
    if (mode == PushButtonMode::modeAdd)
    {
        slotSetModeToModeAdd();
    }
    else if (mode == PushButtonMode::modeEdit)
    {
        slotSetModeToModeEdit();
    }
    // With change in mode, initially we disable the button:
    setEnabled(false);
}

void PushButtonRecordEdit::slotSetModeToModeEdit()
{
    m_mode = PushButtonMode::modeEdit;
    setText(ButtonTextModeEdit);
}
void PushButtonRecordEdit::slotSetModeToModeAdd()
{
    m_mode = PushButtonMode::modeAdd;
    setText(ButtonTextModeAdd);
}

void PushButtonRecordEdit::slotSendConfirmationSignal()
{
    if (m_mode == PushButtonMode::modeAdd)
    {
        emit signalConfirmInsert();
    }
    else if (m_mode == PushButtonMode::modeEdit)
    {
        emit signalConfirmEdit();
    }
}


