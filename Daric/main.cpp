#include "MainWindow.h"
#include <QApplication>

#include "CreateSqliteDatabase.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();

//    CreateSqliteDatabase db;
//    return 0;
}
