#ifndef TESTDEBUGWIDGETS_H
#define TESTDEBUGWIDGETS_H

#include <QObject>

class MainWindow;
class TestDebugWidgets : public QObject
{
    Q_OBJECT
public:
    TestDebugWidgets(QObject* parent = nullptr);

private slots:
    void slotTestDebugPushButton();


private:
    MainWindow* m_mainWindow;
};

#endif // TESTDEBUGWIDGETS_H
