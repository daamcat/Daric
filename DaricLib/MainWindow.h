#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>


class DatabaseManager;
class WalletFilterDialog;
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
    void openWalletFilterDialog();


    Ui::MainWindow *ui;

    DatabaseManager* m_manager;
    WalletFilterDialog* m_walletFilterDialog;

private slots:
    void slotPushButtonDebugClicked();

};

#endif // MAINWINDOW_H
