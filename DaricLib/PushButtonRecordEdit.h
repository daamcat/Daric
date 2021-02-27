#ifndef PUSHBUTTONRECORDEDIT_H
#define PUSHBUTTONRECORDEDIT_H

#include <QPushButton>

enum class PushButtonMode
{
    editMode,
    addMode
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
    void slotSetModeToEditMode();
    void slotSetModeToAddMode();

private slots:
    void slotSendConfirmationSignal();

signals:
    void signalConfirmEdit();
    void signalConfirmInsert();

private:
    PushButtonMode m_mode = PushButtonMode::addMode;

    const QString ButtonTextEditMode = "Confirm";
    const QString ButtonTextAddMode = "Insert";
};

#endif // PUSHBUTTONRECORDEDIT_H
