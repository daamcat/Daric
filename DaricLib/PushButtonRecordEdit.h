#ifndef PUSHBUTTONRECORDEDIT_H
#define PUSHBUTTONRECORDEDIT_H

#include <QPushButton>

enum class PushButtonMode
{
    modeEdit,
    modeAdd
};

class PushButtonRecordEdit : public QPushButton
{
    Q_OBJECT
public:
    PushButtonRecordEdit(QWidget* parent = nullptr);


public slots:
    void slotSetDisabled();
    void slotSetEnabled();
    void slotSetMode(PushButtonMode mode);
    void slotSetModeToModeEdit();
    void slotSetModeToModeAdd();

private slots:
    void slotSendConfirmationSignal();

signals:
    void signalConfirmEdit();
    void signalConfirmInsert();

private:
    PushButtonMode m_mode = PushButtonMode::modeAdd;

    const QString ButtonTextModeEdit = "Confirm";
    const QString ButtonTextModeAdd = "Insert";
};

#endif // PUSHBUTTONRECORDEDIT_H
