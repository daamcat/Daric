#include "WidgetDropBox.h"
#include "ui_WidgetDropBoxForm.h"

#include "dropbox/DropboxClient.h"
#include "dropbox/users/UsersRoutes.h"
#include "dropbox/endpoint/DropboxAppInfo.h"
#include "dropbox/endpoint/DropboxAuthInfo.h"


#include <QFile>

WidgetDropBox::WidgetDropBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetDropBox)
{
    ui->setupUi(this);

    if (!QFile::exists("token.info"))
        // If token file doesn't exist,...
    {

    }
    //###########################
    // Authorize
    //###########################


    QString argAuthFile = "C:/Projects/DropboxQt/dropboxQt-master-temp/examples/account-info/debug/token.info";
    dropboxQt::DropboxAuthInfo authInfo;
    // Read auth info file.
    if(!authInfo.readFromFile(argAuthFile))
    {
        ui->labelDropBox->setText("Error reading <auth-file>");
    }

    dropboxQt::DropboxClient c(authInfo.getAccessToken());
    try
        {
            std::unique_ptr<dropboxQt::users::FullAccount> accountInfo = c.getUsers()->getCurrentAccount();
            ui->labelDropBox->setText(accountInfo->toString());
        }
    catch(dropboxQt::DropboxException& e)
        {
            ui->labelDropBox->setText("Exception: " + QString::fromStdString((e.what())));
        }

}

WidgetDropBox::~WidgetDropBox()
{
    delete ui;
}
