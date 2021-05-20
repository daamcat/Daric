#include "CostEntryForm.h"
#include "ui_CostEntryForm.h"

#include "DatabaseManager.h"
#include "Configuration.h"
#include "MySqlTableModel2.h"

#include <QDebug>

CostEntryForm::CostEntryForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CostEntryForm)
{
    ui->setupUi(this);
    Configuration config;

    m_tags = DatabaseManager::getFieldsFromForeignKeyTable(config.databaseName, config.TableNameTag);
    for (QString e : m_tags.values())
    {
        ui->comboBoxTag->addItem(e);
    }

    m_shoppingSources = DatabaseManager::getFieldsFromForeignKeyTable(config.databaseName, config.TableNameShoppingSource);
    for (QString e : m_shoppingSources.values())
    {
        ui->comboBoxShoppingSource->addItem(e);
    }

    m_paymentMeans = DatabaseManager::getFieldsFromForeignKeyTable(config.databaseName, config.TableNamePaymentMean);
    for (QString e : m_paymentMeans.values())
    {
        ui->comboBoxPaymentMean->addItem(e);
    }

    m_currencies = DatabaseManager::getFieldsFromForeignKeyTable(config.databaseName, config.TableNameCurrency);
    for (QString e : m_currencies.values())
    {
        ui->comboBoxCurrency->addItem(e);
    }

    connect(ui->pushButtonInsert, &QPushButton::clicked, this, &CostEntryForm::insertRecord);
}

CostEntryForm::~CostEntryForm()
{
    delete ui;
}

void CostEntryForm::mousePressEvent(QMouseEvent* event)
{
    qDebug()<<"Mouse button is pressed on NewRecordWidget!";
}

void CostEntryForm::setSqlTableModel(MySqlTableModel2* tableModel)
{
    m_tableModel = tableModel;
}

void CostEntryForm::insertRecord()
{
    QMap<int,QString> values;

    qint64 dateTimeNow = QDateTime::currentDateTime().toMSecsSinceEpoch();
    //"InsertionDateTime INTEGER NOT NULL UNIQUE,"
    values[0] = QString::number(dateTimeNow);
    //"Description TEXT,"
    values[1] = ui->lineEditDescription->text();
    //"Price REAL NOT NULL,"
    values[2] = ui->doubleSpinBoxPrice->text();
    //"ShoppingDate INTEGER,"
    values[3] = QString::number(ui->dateEditShoppingDate->date().toJulianDay());
    //"Withdrawal REAL,"
    values[4] = QString::number(ui->pushButtonWithdrawal->isChecked() ? 1 : 0);
    //"Tag INTEGER,"
    values[5] = QString::number(m_tags.key(ui->comboBoxTag->currentText()));
    //"Currency INTEGER,"
    values[6] = QString::number(m_currencies.key(ui->comboBoxCurrency->currentText()));
    //"LastEditDateTime INTEGER,"
    // We set it equal to insertion date-time.
    values[7] = QString::number(dateTimeNow);
    //"PaymentMean INTEGER,"
    values[8] = QString::number(m_paymentMeans.key(ui->comboBoxPaymentMean->currentText()));
    //"ShoppingSource INTEGER);";
    values[9] = QString::number(m_shoppingSources.key(ui->comboBoxShoppingSource->currentText()));

    m_tableModel->addRecord(-1,values); // -1: Add record to the end of model.
}

