#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QObject>
#include <QString>

class Configuration : public QObject
{
    Q_OBJECT
public:
    Configuration(QObject* parent = nullptr);

    const QString databaseName = QString(SOURCE_DIR) + "/testData/newDB.sqlite";
    const QString sampleBillImageName = QString(SOURCE_DIR) + "/testData/sampleBill.jpg";
    const QString sampleBillImageName2 = QString(SOURCE_DIR) + "/testData/sampleBill2.jpg";

    const QString debugTestString = "This is a test string!";


    const int visibilityLevelUser = 20;
    const int visibilityLevelDebug = 80;


    const QString tableNamePropertiesEnding = "_properties";
    const QString dateTimeDisplayFormat = "dd.MM.yyyy-hh:mm:ss";
    const QString dateDisplayFormat = "dd.MM.yyyy";

    const QString foreignKeyTableIdHeader = "ID";

    const QString TableNameCosts = "Costs";
    const QString TableNameTag = "Tag";
    const QString TableNameCurrency = "Currency";
    const QString TableNamePaymentMean = "PaymentMean";
    const QString TableNameShoppingSource = "ShoppingSource";

    const QString fieldNameShoppingDate = "ShoppingDate";


};

#endif // CONFIGURATION_H
