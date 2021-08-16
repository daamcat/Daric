#ifndef WALLETFILTERDIALOG_H
#define WALLETFILTERDIALOG_H

#include <QDialog>

namespace Ui {
class WalletFilterDialog;
}

class WalletFilterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WalletFilterDialog(QWidget *parent = nullptr);
    ~WalletFilterDialog();

private:
    Ui::WalletFilterDialog *ui;
};

#endif // WALLETFILTERDIALOG_H
