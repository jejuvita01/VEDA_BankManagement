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
#include <QLocale>
#include <QInputDialog>

UserWidget::UserWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UserWidget)
{
    ui->setupUi(this);
    person = new User();
    ui->depositBtn->setChecked(true);

    stackedLayout = new QStackedLayout(this);
    ui->inputGroupBox->setLayout(stackedLayout);
    // 보통 예금 개설 위젯
    depositWidget = new QWidget(this);
    depositLayout = new QFormLayout(this);
    depositBalanceSpinBox = new QSpinBox(this);
    depositBalanceSpinBox->setStyleSheet("QSpinBox {padding: 4px 4px 4px 4px}");
    depositBalanceSpinBox->setRange(0, 1000000000);
    depositBalanceSpinBox->setGroupSeparatorShown(true);
    depositBalanceSpinBox->selectAll();
    depositBalanceSpinBox->setSingleStep(10000);
    depositBalanceSpinBox->setSuffix(tr("원"));
    depositCompleteButton = new QPushButton(tr("개설 완료"), this);
    depositLayout->addRow(new QLabel("금액"), depositBalanceSpinBox);
    depositLayout->addRow(new QLabel(""), depositCompleteButton);
    depositWidget->setLayout(depositLayout);
    // 정기 예금 개설 위젯
    savingWidget = new QWidget(this);
    savingLayout = new QFormLayout(this);
    savingBalanceSpinBox = new QSpinBox(this);
    savingBalanceSpinBox->setStyleSheet("QSpinBox {padding: 4px 4px 4px 4px}");
    savingBalanceSpinBox->setRange(0, 1000000000);
    savingBalanceSpinBox->setGroupSeparatorShown(true);
    savingBalanceSpinBox->selectAll();
    savingBalanceSpinBox->setSingleStep(10000);
    savingBalanceSpinBox->setSuffix(tr("원"));
    savingDurationSpinBox = new QSpinBox(this);
    savingDurationSpinBox->setStyleSheet("QSpinBox {padding: 4px 4px 4px 4px}");
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
    // 화면 전환 시 focus 변환
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
        int money = depositBalanceSpinBox->value();
        person->make_deposit(money);
        refreshTable();
        // 계좌 완료되면, 전체 계좌 조회로 화면 전환
        depositBalanceSpinBox->setValue(0);
        ui->tabWidget->setCurrentIndex(0);
        ui->showAllAccount->setFocus();
    });

    connect(savingCompleteButton, &QPushButton::clicked, this, [=]() {
        // 정기 예금 계좌 개설 하기
        int money = savingBalanceSpinBox->value();
        int year = savingDurationSpinBox->value();
        person->make_saving(money, year);
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

    connect(ui->logoutBtn, &QPushButton::clicked, this, [=]() {
        setPerson(nullptr);
        emit switchToMainScreen();
    });

    connect(ui->withdrawBtn, &QPushButton::clicked, this, [=]() {
        setPerson(nullptr);
        emit withdrawUser(this->id);
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

void UserWidget::setId(string id) {
    this->id = id;
}

void UserWidget::refreshTable()
{
    ui->accountTableWidget->reset();

    if (person == nullptr) return;

    vector<Account*> accounts = person->get_accounts();

    ui->accountTableWidget->setRowCount(accounts.size());
    QTableWidgetItem* item;
    QLocale locale = QLocale::system();
    for (int i = 0; i < accounts.size(); i++) {
        Account* account = accounts[i];
        if (dynamic_cast<Deposit*>(account)) {
            item = new QTableWidgetItem(tr("보통 예금"));
            item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            ui->accountTableWidget->setItem(i, 0, item);
            item = new QTableWidgetItem(tr("X"));
            item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            ui->accountTableWidget->setItem(i, 2, item);
        }
        else if (dynamic_cast<Saving*>(account)) {
            item = new QTableWidgetItem(tr("정기 예금"));
            item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            ui->accountTableWidget->setItem(i, 0, item);
            item = new QTableWidgetItem(QString::number(account->get_duration() / 12));
            item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            ui->accountTableWidget->setItem(i, 2, item);
        }
        item = new QTableWidgetItem(locale.toString(account->get_balance()));
        item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        item->setFlags(item->flags() & ~Qt::ItemIsEditable);
        ui->accountTableWidget->setItem(i, 1, item);

        item = new QTableWidgetItem(QString::fromStdString(make_time_string(account->get_start_date())));
        item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        item->setFlags(item->flags() & ~Qt::ItemIsEditable);
        ui->accountTableWidget->setItem(i, 3, item);


        QPushButton* button = new QPushButton(tr("입금"), ui->accountTableWidget);
        connect(button, &QPushButton::clicked, this, [=](){
            bool ok;
            int money = QInputDialog::getInt(this, tr("입금"), tr("입금하실 금액을 입력해주세요."), 0, 0, MAX_BALANCE - account->get_balance(), 1, &ok);
            if (ok && money > 0) {
                account->deposit(money);
                refreshTable();
            }
        });
        ui->accountTableWidget->setCellWidget(i, 4, button);

        button = new QPushButton(tr("출금"), ui->accountTableWidget);
        connect(button, &QPushButton::clicked, this, [=](){
            bool ok;
            int money = QInputDialog::getInt(this, tr("출금"), tr("출금하실 금액을 입력해주세요."), 0, 0, account->get_balance(), 1, &ok);
            if (ok && money > 0) {
                account->withdraw(money);
                refreshTable();
            }
        });
        ui->accountTableWidget->setCellWidget(i, 5, button);

        button = new QPushButton(tr("해지"), ui->accountTableWidget);
        connect(button, &QPushButton::clicked, this, [=](){
            person->erase_account(i);
            refreshTable();
        });
        ui->accountTableWidget->setCellWidget(i, 6, button);
    }
}
