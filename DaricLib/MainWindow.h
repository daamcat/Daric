#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


class DatabaseManager;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    DatabaseManager* m_manager;

private slots:
    void slotPushButtonDebugClicked();
};

#endif // MAINWINDOW_H
