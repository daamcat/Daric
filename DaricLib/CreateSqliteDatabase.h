#ifndef CREATESQLITEDATABASE_H
#define CREATESQLITEDATABASE_H

#include <QString>
#include <QVector>



struct DisplayType
{
    enum class DisplayTypeEnum
    {
        foreignKey = 0,
        date = 1,
        dateTime = 2,
        text = 3,
        integer = 4,
        real = 5
    };
    static QString enumToString(DisplayTypeEnum en)
    {
        switch (en)
        {
        case DisplayTypeEnum::foreignKey:
            return QString("foreignKey");
        case DisplayTypeEnum::date:
            return QString("date");
        case DisplayTypeEnum::dateTime:
            return QString("dateTime");
        case DisplayTypeEnum::text:
            return QString("text");
        case DisplayTypeEnum::integer:
            return QString("integer");
        case DisplayTypeEnum::real:
            return QString("real");
        }
    }

    static int enumToInt(DisplayTypeEnum en)
    {
        return static_cast<int>(en);
    }

    static DisplayTypeEnum intToEnum(int en)
    {
        return static_cast<DisplayTypeEnum>(en);
    }

    // Order is important:
    static QVector<QString> elements() { return QVector<QString>({"foreignKey",
                                                                  "date",
                                                                  "dateTime",
                                                                  "text",
                                                                  "integer",
                                                                  "real"});}
};

struct DataType
{
    enum class DataTypeEnum
    {
        INTEGER = 0,
        TEXT = 1,
        BLOB = 2,
        REAL = 3,
        NUMERIC = 4
    };
    static QString enumToString(DataTypeEnum en)
    {
        switch (en)
        {
        case DataTypeEnum::INTEGER:
            return QString("INTEGER");
        case DataTypeEnum::TEXT:
            return QString("TEXT");
        case DataTypeEnum::BLOB:
            return QString("BLOB");
        case DataTypeEnum::REAL:
            return QString("REAL");
        case DataTypeEnum::NUMERIC:
            return QString("NUMERIC");
        }
    }
    // Order is important:
    static QVector<QString> elements() { return QVector<QString>({"INTEGER",
                                                                  "TEXT",
                                                                  "BLOB",
                                                                  "REAL",
                                                                  "NUMERIC"});}
};

struct Field
{
    QString fieldName;
    QString fieldHeaderViewName;
    QString dataType;
    QString properties;
    int editable; // Because SQLITE has no boolean type.
    int foreignKey;
    DisplayType::DisplayTypeEnum displayType;
    int nullValid; // Means "must be entered"
    int autoGenerated;
    int visibilityLevel;

    static QVector<QString> elements() { return QVector<QString>({"fieldName",
                                                                  "fieldHeaderViewName",
                                                                  "dataType",
                                                                  "properties",
                                                                  "editable",
                                                                  "foreignKey",
                                                                  "displayType",
                                                                  "nullValid",
                                                                  "autoGenerated",
                                                                  "visibilityLevel"});}
};


struct Tag
{
    enum class TagEnum
    {
        travel = 0,
        leisure = 1,
        grocery = 2
    };
    static QString enumToString(TagEnum en)
    {
        switch (en)
        {
        case TagEnum::travel:
            return QString("travel");
        case TagEnum::leisure:
            return QString("leisure");
        case TagEnum::grocery:
            return QString("grocery");
        }
    }
    // Order is important:
    static QVector<QString> elements() { return QVector<QString>({"travel", "leisure", "grocery"});}
};


struct ShoppingSource
{
    enum class ShoppingSourceEnum
    {
        amazon = 0,
        ebay = 1,
    };
    static QString enumToString(ShoppingSourceEnum en)
    {
        switch (en)
        {
        case ShoppingSourceEnum::amazon:
            return QString("amazon");
        case ShoppingSourceEnum::ebay:
            return QString("ebay");
        }
    }
    // Order is important:
    static QVector<QString> elements() { return QVector<QString>({"amazon", "ebay"});}
};

struct PaymentMean
{
    enum class PaymentMeanEnum
    {
        amazon = 0,
        ebay = 1,
    };
    static QString enumToString(PaymentMeanEnum en)
    {
        switch (en)
        {
        case PaymentMeanEnum::amazon:
            return QString("cash");
        case PaymentMeanEnum::ebay:
            return QString("MasterCard");
        }
    }
    // Order is important:
    static QVector<QString> elements() { return QVector<QString>({"cash", "MasterCard"});}
};

struct Currency
{
    enum class CurrencyEnum
    {
        dollar = 0,
        euro = 1,
        toman = 2
    };
    static QString enumToString(CurrencyEnum en)
    {
        switch (en)
        {
        case CurrencyEnum::dollar:
            return QString("dollar");
        case CurrencyEnum::euro:
            return QString("euro");
        case CurrencyEnum::toman:
            return QString("toman");
        }
    }
    // Order is important:
    static QVector<QString> elements() { return QVector<QString>({"dollar", "euro", "toman"});}
};


class CreateSqliteDatabase
{
public:
    CreateSqliteDatabase();

private:
    QVector<Field> m_tableCosts;
    QVector<Field> m_tableForeignKeysTag;
    QVector<Field> m_tableForeignKeysPaymentMean;
    QVector<Field> m_tableForeignKeysShoppingSource;
    QVector<Field> m_tableForeignKeysCurrency;
    QVector<Field> m_tableForeignKeysDisplayType;
    QVector<Field> m_tableForeignKeysDataType;
    QVector<Field> m_tableProperties;

};

#endif // CREATESQLITEDATABASE_H
