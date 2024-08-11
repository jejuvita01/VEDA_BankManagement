#include "userwidget.h"
#include "ui_userwidget.h"
#include "user.h"
#include "person.h"
#include "account.h"
#include "deposit.h"
#include "saving.h"
#include "utility.h"

#include <vector>
#include <QStringList>
#include <QTableWidgetItem>
#include <QFormLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QLabel>
#include <QSpinBox>
#include <QStackedLayout>

UserWidget::UserWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UserWidget)
{
    ui->setupUi(this);
    person = new User();
    ui->depositBtn->setChecked(true);

    stackedLayout = new QStackedLayout(this);
    ui->inputGroupBox->setLayout(stackedLayout);

    depositWidget = new QWidget(this);
    depositLayout = new QFormLayout(this);
    depositBalanceSpinBox = new QSpinBox(this);
    depositBalanceSpinBox->setRange(0, 1000000000);
    depositBalanceSpinBox->setGroupSeparatorShown(true);
    depositBalanceSpinBox->selectAll();
    depositBalanceSpinBox->setSingleStep(10000);
    depositBalanceSpinBox->setSuffix(tr("원"));
    depositCompleteButton = new QPushButton(tr("개설 완료"), this);
    depositLayout->addRow(new QLabel("금액"), depositBalanceSpinBox);
    depositLayout->addRow(new QLabel(""), depositCompleteButton);
    depositWidget->setLayout(depositLayout);

    savingWidget = new QWidget(this);
    savingLayout = new QFormLayout(this);
    savingBalanceSpinBox = new QSpinBox(this);
    savingBalanceSpinBox->setRange(0, 1000000000);
    savingBalanceSpinBox->setGroupSeparatorShown(true);
    savingBalanceSpinBox->selectAll();
    savingBalanceSpinBox->setSingleStep(10000);
    savingBalanceSpinBox->setSuffix(tr("원"));
    savingDurationSpinBox = new QSpinBox(this);
    savingDurationSpinBox->setRange(1, 5);
    savingDurationSpinBox->setSingleStep(1);
    savingDurationSpinBox->setSuffix(tr("년"));
    savingCompleteButton = new QPushButton(tr("개설 완료"), this);
    savingLayout->addRow(new QLabel("금액"), savingBalanceSpinBox);
    savingLayout->addRow(new QLabel("기간"), savingDurationSpinBox);
    savingLayout->addRow(new QLabel(""), savingCompleteButton);
    savingWidget->setLayout(savingLayout);

    stackedLayout->insertWidget(0, depositWidget);
    stackedLayout->insertWidget(1, savingWidget);

    ui->tabWidget->setCurrentIndex(0);
    connect(ui->depositBtn, &QRadioButton::clicked, this, [=]() {
        stackedLayout->setCurrentIndex(0);
        depositBalanceSpinBox->setFocus();
    });

    connect(ui->savingBtn, &QRadioButton::clicked, this, [=]() {
        stackedLayout->setCurrentIndex(1);
        savingBalanceSpinBox->setFocus();
    });

    connect(depositCompleteButton, &QPushButton::clicked, this, [=]() {
        // 일반 예금 계좌 개설 하기


        refreshTable();
        // 계좌 완료되면, 전체 계좌 조회로 화면 전환
        depositBalanceSpinBox->setValue(0);
        ui->tabWidget->setCurrentIndex(0);
        ui->showAllAccount->setFocus();
    });

    connect(savingCompleteButton, &QPushButton::clicked, this, [=]() {
        // 정기 예금 계좌 개설 하기

        refreshTable();
        // 화면 전환
        savingBalanceSpinBox->setValue(0);
        savingDurationSpinBox->setValue(1);
        ui->tabWidget->setCurrentIndex(0);
        ui->showAllAccount->setFocus();
    });

    connect(ui->tabWidget, &QTabWidget::currentChanged, this, [=](int index) {
        if (index == 0) ui->showAllAccount->setFocus();
        else if (index == 1) {
            if (ui->depositBtn->isChecked())
                depositBalanceSpinBox->setFocus();
            else if (ui->savingBtn->isChecked())
                savingBalanceSpinBox->setFocus();
        }
    });
}

UserWidget::~UserWidget()
{
    delete ui;
}

void UserWidget::setPerson(Person *person)
{
    this->person = person;
    refreshTable();
}

void UserWidget::refreshTable()
{
    ui->accountTableWidget->reset();

    vector<Account*> accounts = person->get_accounts();
    QTableWidgetItem* item;
    for (int i = 0; i < accounts.size(); i++) {
        Account* account = accounts[i];
        if (dynamic_cast<Deposit*>(account)) {
            item = new QTableWidgetItem(tr("보통 예금"));
        }
        if (dynamic_cast<Saving*>(account)) {
            item = new QTableWidgetItem(tr("정기 예금"));
        }
        ui->accountTableWidget->setItem(i, 0, item);

        item = new QTableWidgetItem(QString::fromStdString(num_to_string_with_comma(account->get_balance())));
        ui->accountTableWidget->setItem(i, 1, item);

        item = new QTableWidgetItem(QString::fromStdString(make_time_string(account->get_start_date())));
        ui->accountTableWidget->setItem(i, 2, item);
    }
}
