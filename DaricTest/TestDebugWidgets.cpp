#include "TestDebugWidgets.h"
#include "MainWindow.h"
#include "Configuration.h"

#include <QTest>
#include <QPushButton>
#include <QLabel>
#include <QDebug>

TestDebugWidgets::TestDebugWidgets(QObject* parent) :
    QObject (parent)
{
    m_mainWindow = new MainWindow();
    m_mainWindow->show();
}

void TestDebugWidgets::slotTestDebugPushButton()
{
    QPushButton* pushButton = m_mainWindow->findChild<QPushButton*>("pushButtonDebug");
    QLabel* label = m_mainWindow->findChild<QLabel*>("labelDebug");

    if (pushButton)
    {
        // Wait one second (qWait: events are processed. qSleep: events are not processed.)
        QTest::qWait(1000);
        QTest::mouseClick(pushButton,Qt::MouseButton::LeftButton);
        QTest::qWait(1000);
    }
    else
    {
        // Force the test to fail:
        QFAIL("Invalid push button");
    }
    if (!label)
    {
        // Force the test to fail:
        QFAIL("Invalid label widget.");
    }

    Configuration config;
    qDebug()<<"Value in label widget: "<< label->text();
    qDebug()<<"Value expected: "<< config.debugTestString;
    QCOMPARE(label->text(), config.debugTestString);
}
