#include "loginwidget.h"
#include "ui_loginwidget.h"
#include "person.h"
#include "user.h"
#include "manager.h"
#include <QLineEdit>
#include <QPushButton>
#include <QApplication>

LoginWidget::LoginWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginWidget)
{
    ui->setupUi(this);
    ui->idLineEdit->setTextMargins(4, 4, 4, 4);
    ui->pwLineEdit->setTextMargins(4, 4, 4, 4);

    connect(ui->backBtn, &QPushButton::clicked, this, [=]() {
        ui->idLineEdit->setText(tr(""));
        ui->pwLineEdit->setText(tr(""));
        emit switchToMainScreen();
    });

    connect(ui->loginBtn, &QPushButton::clicked, this, &LoginWidget::login);
    connect(ui->idLineEdit, &QLineEdit::returnPressed, this, &LoginWidget::login);
}

LoginWidget::~LoginWidget()
{
    delete ui;
}

// public 함수
void LoginWidget::setData(map<string, pair<string, Person*>> d) {
    this->data = d;
}

// slot 함수
void LoginWidget::login() {
    auto found = data.find(ui->idLineEdit->text().toStdString());
    string pwInput = ui->pwLineEdit->text().toStdString();
    if (pwInput.empty()) {
        ui->messageLabel->setText("비밀 번호를 입력해주세요.");
        ui->messageLabel->setStyleSheet(tr("QLabel { color : red; }"));
        return;
    }
    if (found == data.end() || found->second.first != pwInput) {
        ui->messageLabel->setText("아이디와 비밀 번호를 찾을 수 없습니다.");
        ui->messageLabel->setStyleSheet(tr("QLabel { color : red; }"));
        return;
    }
    else {
        if (dynamic_cast<User*>(found->second.second)) {
            qDebug() << "유저입니다.";
            emit switchToUserScreen();
        }
        else if (dynamic_cast<Manager*>(found->second.second)) {
            qDebug() << "매니저입니다.";
            emit switchToManagerScreen();
        }
    }
}
