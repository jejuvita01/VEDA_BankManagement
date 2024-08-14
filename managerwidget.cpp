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

    connect(ui->userDeleteButton, &QPushButton::clicked, this, [=]() {
        qDebug() << "유저 삭제";
        string del_id;
        int c, r;
        c = ui->userIdTableWidget->currentColumn();
        r = ui->userIdTableWidget->currentRow();
        del_id = (ui->userIdTableWidget->takeItem(r, c)->text().toStdString());
        emit withdrawUser(del_id);
        refreshUserDeleteTable();
        refreshUserSearchTable(string(""));
        ui->userAccountsTabelWidget->setRowCount(0);
        ui->userAccountsTabelWidget->clearSelection();
        ui->userAccountsTabelWidget->reset();
        ui->userAccountsTabelWidget->clear();

    });
    refreshUserSearchTable("");
}

ManagerWidget::~ManagerWidget()
{
    delete ui;
}

void ManagerWidget::setData(map<string, pair<string, Person*>> d) {
    this->data = d;
    refreshUserSearchTable(string(""));
    refreshUserDeleteTable();
}

void ManagerWidget::setPerson(Person* person) {
    this->person = person;
}

void ManagerWidget::setId(string id) {
    this->id = id;
}

void ManagerWidget::refreshUserSearchTable(string searchId) {
    ui->userSearchTableWidget->reset();

    int cnt = 0;
    for (const auto& d: data) {
        if (dynamic_cast<Manager*>(d.second.second))
            continue;
        if (d.first.find(searchId) != string::npos) {
            User* u = dynamic_cast<User*>(d.second.second);
            if (u == nullptr)
                continue;
            else {
            for (const auto& a: u->get_accounts())
                cnt++;
            }
        }
    }

    qDebug() << "CNT: " << cnt;

    ui->userSearchTableWidget->setRowCount(cnt);

    int row = 0;
    QTableWidgetItem* item;
    for (const auto& datum : data) {
        qDebug() << datum.first;
        if (dynamic_cast<Manager*>(datum.second.second)) continue;
        string userId = datum.first;
        qDebug() << "유저" << userId;
        if (userId.find(searchId) == string::npos) continue;
        qDebug() << "유저" << userId << searchId << "포함";

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

    int cnt = 0;
    for (const auto& d: data) {
        if (dynamic_cast<Manager*>(d.second.second))
            continue;
        else
            cnt++;
    }

    ui->userIdTableWidget->setRowCount(cnt);

    int row = 0;
    QTableWidgetItem* item;
    for (const auto& datum : data) {
        qDebug() << datum.first;
        if (dynamic_cast<Manager*>(datum.second.second)) continue;

        item = new QTableWidgetItem(QString::fromStdString(datum.first));
        ui->userIdTableWidget->setItem(row++, 0, item);
        connect(ui->userIdTableWidget, &QTableWidget::itemClicked, this, &ManagerWidget::refreshUserAccountsTable);
    }
    ui->userAccountsTabelWidget->setRowCount(0);
    ui->userAccountsTabelWidget->clearSelection();
    ui->userAccountsTabelWidget->reset();
    ui->userAccountsTabelWidget->clear();
}
void ManagerWidget::refreshUserAccountsTable(QTableWidgetItem* item) {
    ui->userAccountsTabelWidget->reset();
    string userId = item->text().toStdString();
    auto found = data.find(userId);
    if (found == data.end()) return;
    QTableWidgetItem* widgetItem;
    ui->userAccountsTabelWidget->setRowCount(found->second.second->get_accounts().size());
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
