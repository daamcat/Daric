#include "CostEntryForm.h"
#include "ui_CostEntryForm.h"

#include "DatabaseManager.h"
#include "Configuration.h"
#include "MySqlTableModel2.h"
#include "ComboBoxCostEntry.h"

#include <QDebug>
#include <QDoubleSpinBox>

CostEntryForm::CostEntryForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CostEntryForm)
{
    ui->setupUi(this);
    Configuration config;

    checkPushButtonStatus();

    ui->comboBoxTag->setItems(DatabaseManager::getFieldsFromForeignKeyTable(config.databaseName, config.TableNameTag));
    ui->comboBoxShoppingSource->setItems(DatabaseManager::getFieldsFromForeignKeyTable(config.databaseName, config.TableNameShoppingSource));
    ui->comboBoxPaymentMean->setItems(DatabaseManager::getFieldsFromForeignKeyTable(config.databaseName, config.TableNamePaymentMean));
    ui->comboBoxCurrency->setItems(DatabaseManager::getFieldsFromForeignKeyTable(config.databaseName, config.TableNameCurrency));

    connect(ui->pushButtonInsert, &QPushButton::clicked, this, &CostEntryForm::insertRecord);
    connect(ui->lineEditDescription, &QLineEdit::textChanged , this , &CostEntryForm::checkPushButtonStatus);
    // Double spinbox has always a value. Hence checking if it is empty or not doesn't make sense.
    connect(ui->doubleSpinBoxPrice, qOverload<const QString&>(&QDoubleSpinBox::valueChanged), this, &CostEntryForm::checkPushButtonStatus);
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
    values[5] = ui->comboBoxTag->getCurrentItem();
    //"Currency INTEGER,"
    values[6] = ui->comboBoxCurrency->getCurrentItem();
    //"LastEditDateTime INTEGER,"
    // We set it equal to insertion date-time.
    values[7] = QString::number(dateTimeNow);
    //"PaymentMean INTEGER,"
    values[8] = ui->comboBoxPaymentMean->getCurrentItem();
    //"ShoppingSource INTEGER);";
    values[9] = ui->comboBoxShoppingSource->getCurrentItem();

    bool success = m_tableModel->addRecord(-1,values); // -1: Add record to the end of model.
    if (success)
    {
        ui->lineEditDescription->clear();
        ui->doubleSpinBoxPrice->clear();
    }
}

void CostEntryForm::checkPushButtonStatus()
{
    ui->pushButtonInsert->setEnabled(!ui->lineEditDescription->text().isEmpty() &&
                                     !ui->doubleSpinBoxPrice->text().isEmpty());
}

