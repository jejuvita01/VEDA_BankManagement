#include "managerwidget.h"
#include "ui_managerwidget.h"
#include "person.h"
#include "user.h"
#include "manager.h"
#include "account.h"
#include "deposit.h"
#include "saving.h"
#include "utility.h"

#include <vector>
#include <QTableWidget>
#include <QTableWidgetItem>

ManagerWidget::ManagerWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ManagerWidget)
{
    ui->setupUi(this);
    connect(ui->userSearchlineEdit, &QLineEdit::textChanged, this, [=](const QString& QId) {
        refreshUserSearchTable(QId.toStdString());
    });

    connect(ui->logoutBtn, &QPushButton::clicked, this, [=]() {
        qDebug() << "로그 아웃";
        setPerson(nullptr);
        emit switchTomainScreen();
    });

    connect(ui->withdrawBtn, &QPushButton::clicked, this, [=]() {
        qDebug() << "매니저 탈퇴";
        setPerson(nullptr);
        emit withdrawManager(this->id);
    });
}

ManagerWidget::~ManagerWidget()
{
    delete ui;
}

void ManagerWidget::setData(map<string, pair<string, Person*>> d) {
    this->data = d;
}

void ManagerWidget::setPerson(Person* person) {
    this->person = person;
}

void ManagerWidget::refreshUserSearchTable(string searchId) {
    ui->userSearchTableWidget->reset();

    int row = 0;
    QTableWidgetItem* item;
    for (const auto& datum : data) {
        if (dynamic_cast<Manager*>(datum.second.second)) continue;
        string userId = datum.first;
        if (userId.find(searchId) == string::npos) continue;

        User* user = dynamic_cast<User*>(datum.second.second);
        vector<Account*> userAccounts = user->get_accounts();

        for (const auto& account : userAccounts) {
            item = new QTableWidgetItem(QString::fromStdString(userId));
            ui->userSearchTableWidget->setItem(row, 0, item);

            if (dynamic_cast<Deposit*>(account)){
                item = new QTableWidgetItem(tr("보통 예금"));
                ui->userSearchTableWidget->setItem(row, 1, item);
                item = new QTableWidgetItem(tr("X"));
                ui->userSearchTableWidget->setItem(row, 3, item);
            }
            else if (dynamic_cast<Saving*>(account)) {
                item = new QTableWidgetItem(tr("정기 예금"));
                ui->userSearchTableWidget->setItem(row, 1, item);
                item = new QTableWidgetItem(QString::number(account->get_duration()));
                ui->userSearchTableWidget->setItem(row, 3, item);
            }

            item = new QTableWidgetItem(QString::number(account->get_balance()));
            ui->userSearchTableWidget->setItem(row, 2, item);

            item = new QTableWidgetItem(QString::fromStdString(make_time_string(account->get_start_date())));
            ui->userSearchTableWidget->setItem(row, 4, item);
            row++;
        }
    }
}

void ManagerWidget::refreshUserDeleteTable() {
    ui->userIdTableWidget->reset();
    int row = 0;
    QTableWidgetItem* item;
    for (const auto& datum : data) {
        if (dynamic_cast<Manager*>(datum.second.second)) continue;

        item = new QTableWidgetItem(QString::fromStdString(datum.first));
        ui->userIdTableWidget->setItem(row++, 0, item);
        connect(ui->userIdTableWidget, &QTableWidget::itemClicked, this, &ManagerWidget::refreshUserAccountsTable);
    }
}
void ManagerWidget::refreshUserAccountsTable(QTableWidgetItem* item) {
    ui->userAccountsTabelWidget->reset();
    string userId = item->text().toStdString();
    auto found = data.find(userId);
    if (found == data.end()) return;
    QTableWidgetItem* widgetItem;
    int row = 0;
    for (const auto& account : found->second.second->get_accounts()) {
        if (dynamic_cast<Deposit*>(account)) {
            widgetItem = new QTableWidgetItem(tr("보통 예금"));
            ui->userAccountsTabelWidget->setItem(row, 0, widgetItem);
            widgetItem = new QTableWidgetItem(tr("X"));
            ui->userAccountsTabelWidget->setItem(row, 2, widgetItem);
        }
        else if (dynamic_cast<Saving*>(account)) {
            widgetItem = new QTableWidgetItem(tr("정기 예금"));
            ui->userAccountsTabelWidget->setItem(row, 0, widgetItem);
            widgetItem = new QTableWidgetItem(QString::number(account->get_duration()));
            ui->userAccountsTabelWidget->setItem(row, 2, widgetItem);
        }

        widgetItem = new QTableWidgetItem(QString::number(account->get_balance()));
        ui->userAccountsTabelWidget->setItem(row, 1, widgetItem);
        widgetItem = new QTableWidgetItem(QString::fromStdString(make_time_string(account->get_start_date())));
        ui->userAccountsTabelWidget->setItem(row, 3, widgetItem);
        row++;
    }
}
