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

UserWidget::UserWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UserWidget)
{
    ui->setupUi(this);
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
    ui->accountTableWidget->setColumnCount(6);
    QStringList header;
    header << "계좌 종류" << "잔액" << "계좌 개설일" << "입금" << "출금" << "해지";
    ui->accountTableWidget->setHorizontalHeaderLabels(header);
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
