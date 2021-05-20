#ifndef IDENTITYPROXYMODEL_H
#define IDENTITYPROXYMODEL_H

#include <QIdentityProxyModel>
#include <QObject>

#include "DatabaseManager.h"
#include "CreateSqliteDatabase.h"
#include "Configuration.h"


// Subclassing QIdentityProxyModel is suitable for when we don't want filtering or sorting job, but
// we want to process the data of model before passing it to view.

class IdentityProxyModel : public QIdentityProxyModel
{
    Q_OBJECT
public:
    IdentityProxyModel(QVector<Field> tableProperties, QObject* parent = nullptr);
    virtual ~IdentityProxyModel();

    QVariant data(const QModelIndex &proxyIndex, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;



private:
    QVector<Field> m_tableProperties;
    Configuration m_config;
};

#endif // IDENTITYPROXYMODEL_H
