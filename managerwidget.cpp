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
#include <QLocale>

ManagerWidget::ManagerWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ManagerWidget)
{
    ui->setupUi(this);
    connect(ui->userSearchlineEdit, &QLineEdit::textChanged, this, [=](const QString& QId) {
        refreshUserSearchTable(QId.toStdString());
    });

    connect(ui->logoutBtn, &QPushButton::clicked, this, [=]() {
        setPerson(nullptr);
        emit switchTomainScreen();
    });

    connect(ui->withdrawBtn, &QPushButton::clicked, this, [=]() {
        setPerson(nullptr);
        emit withdrawManager(this->id);
    });

    connect(ui->userDeleteButton, &QPushButton::clicked, this, [=]() {
        string del_id;
        int c, r;
        c = ui->userIdTableWidget->currentColumn();
        r = ui->userIdTableWidget->currentRow();
        del_id = (ui->userIdTableWidget->takeItem(r, c)->text().toStdString());
        emit withdrawUser(del_id);
        refreshUserDeleteTable();
        refreshUserSearchTable(string(""));
        ui->userAccountsTabelWidget->setRowCount(0);
        ui->userAccountsTabelWidget->clearContents();

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
    ui->userSearchTableWidget->clearContents();

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


    ui->userSearchTableWidget->setRowCount(cnt);

    int row = 0;
    QTableWidgetItem* item;
    QLocale locale = QLocale::system();
    for (const auto& datum : data) {
        if (dynamic_cast<Manager*>(datum.second.second)) continue;
        string userId = datum.first;
        if (userId.find(searchId) == string::npos) continue;

        User* user = dynamic_cast<User*>(datum.second.second);
        vector<Account*> userAccounts = user->get_accounts();

        for (const auto& account : userAccounts) {
            item = new QTableWidgetItem(QString::fromStdString(userId));
            item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            ui->userSearchTableWidget->setItem(row, 0, item);

            if (dynamic_cast<Deposit*>(account)){
                item = new QTableWidgetItem(tr("보통 예금"));
                item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
                item->setFlags(item->flags() & ~Qt::ItemIsEditable);
                ui->userSearchTableWidget->setItem(row, 1, item);
                item = new QTableWidgetItem(tr("X"));
                item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
                item->setFlags(item->flags() & ~Qt::ItemIsEditable);
                ui->userSearchTableWidget->setItem(row, 3, item);
            }
            else if (dynamic_cast<Saving*>(account)) {
                item = new QTableWidgetItem(tr("정기 예금"));
                item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
                item->setFlags(item->flags() & ~Qt::ItemIsEditable);
                ui->userSearchTableWidget->setItem(row, 1, item);
                item = new QTableWidgetItem(QString::number(account->get_duration()));
                item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
                item->setFlags(item->flags() & ~Qt::ItemIsEditable);
                ui->userSearchTableWidget->setItem(row, 3, item);
            }

            item = new QTableWidgetItem(locale.toString(account->get_balance()));
            item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            ui->userSearchTableWidget->setItem(row, 2, item);

            item = new QTableWidgetItem(QString::fromStdString(make_time_string(account->get_start_date())));
            item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            ui->userSearchTableWidget->setItem(row, 4, item);
            row++;
        }
    }
}

void ManagerWidget::refreshUserDeleteTable() {
    ui->userIdTableWidget->clearContents();

    int cnt = 0;
    for (const auto& d: data) {
        if (dynamic_cast<Manager*>(d.second.second))
            continue;
        else
            cnt++;
    }

    ui->userIdTableWidget->setRowCount(cnt);
    ui->userIdTableWidget->verticalHeader()->setVisible(false);

    int row = 0;
    QTableWidgetItem* item;
    for (const auto& datum : data) {
        if (dynamic_cast<Manager*>(datum.second.second)) continue;

        item = new QTableWidgetItem(QString::fromStdString(datum.first));
        item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        item->setFlags(item->flags() & ~Qt::ItemIsEditable);
        ui->userIdTableWidget->setItem(row++, 0, item);
        connect(ui->userIdTableWidget, &QTableWidget::itemClicked, this, &ManagerWidget::refreshUserAccountsTable);
    }
    ui->userAccountsTabelWidget->clearContents();
}
void ManagerWidget::refreshUserAccountsTable(QTableWidgetItem* item) {
    ui->userAccountsTabelWidget->clearContents();
    string userId = item->text().toStdString();
    auto found = data.find(userId);
    if (found == data.end()) return;
    QTableWidgetItem* widgetItem;
    QLocale locale = QLocale::system();
    ui->userAccountsTabelWidget->setRowCount(found->second.second->get_accounts().size());
    int row = 0;
    for (const auto& account : found->second.second->get_accounts()) {
        if (dynamic_cast<Deposit*>(account)) {
            widgetItem = new QTableWidgetItem(tr("보통 예금"));
            widgetItem->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            widgetItem->setFlags(item->flags() & ~Qt::ItemIsEditable);
            ui->userAccountsTabelWidget->setItem(row, 0, widgetItem);
            widgetItem = new QTableWidgetItem(tr("X"));
            widgetItem->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            widgetItem->setFlags(item->flags() & ~Qt::ItemIsEditable);
            ui->userAccountsTabelWidget->setItem(row, 2, widgetItem);
        }
        else if (dynamic_cast<Saving*>(account)) {
            widgetItem = new QTableWidgetItem(tr("정기 예금"));
            widgetItem->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            widgetItem->setFlags(item->flags() & ~Qt::ItemIsEditable);
            ui->userAccountsTabelWidget->setItem(row, 0, widgetItem);
            widgetItem = new QTableWidgetItem(QString::number(account->get_duration()));
            widgetItem->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            widgetItem->setFlags(item->flags() & ~Qt::ItemIsEditable);
            ui->userAccountsTabelWidget->setItem(row, 2, widgetItem);
        }

        widgetItem = new QTableWidgetItem(locale.toString(account->get_balance()));
        widgetItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        widgetItem->setFlags(item->flags() & ~Qt::ItemIsEditable);
        ui->userAccountsTabelWidget->setItem(row, 1, widgetItem);
        widgetItem = new QTableWidgetItem(QString::fromStdString(make_time_string(account->get_start_date())));
        widgetItem->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        widgetItem->setFlags(item->flags() & ~Qt::ItemIsEditable);
        ui->userAccountsTabelWidget->setItem(row, 3, widgetItem);
        row++;
    }
}
