#include "signupwidget.h"
#include "ui_signupwidget.h"
#include <QLineEdit>
#include <QLabel>

SignUpWidget::SignUpWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SignUpWidget)
{
    ui->setupUi(this);
    idCheck = false;
    pwCheck = false;
    ui->idLineEdit->setTextMargins(4, 4, 4, 4);
    ui->pwdLineEdit->setTextMargins(4, 4, 4, 4);
    ui->pwdCheckLineEdit->setTextMargins(4, 4, 4, 4);

    connect(ui->completeBtn, &QPushButton::clicked, this, &SignUpWidget::checkIdAndPw);
    connect(ui->idCheckBtn, &QPushButton::clicked, this, &SignUpWidget::checkId);
    connect(ui->idLineEdit, &QLineEdit::textChanged, this, [=]() { idCheck = false; });
    connect(ui->pwdCheckLineEdit, &QLineEdit::textChanged, this, &SignUpWidget::checkPwCheck);
    connect(ui->backBtn, &QPushButton::clicked, this, [=]() {
        ui->idLineEdit->setText(tr(""));
        ui->pwdLineEdit->setText(tr(""));
        emit switchToMainScreen();
    });
}

SignUpWidget::~SignUpWidget()
{
    delete ui;
}

// private 함수
void SignUpWidget::setMessageLabel(QLabel* label, QString message, QString styleSheet) {
    label->setText(message);
    label->setStyleSheet(styleSheet);
}

// public 함수

void SignUpWidget::insertData(vector<string> data) {
    for (const auto& id : data) {
        ids.push_back(QString::fromStdString(id));
    }
}

// SLOT 함수
void SignUpWidget::checkIdAndPw() {
    qDebug() << "완료 버튼" << "아이디 비번 체크";
    if (ui->idLineEdit->text().length() == 0) {
        setMessageLabel(ui->idMessageLabel, tr("아이디를 입력해주세요"), tr(""));
        return;
    }
    if (!idCheck) {
        setMessageLabel(ui->idMessageLabel, tr("중복 체크 해주세요."), tr(""));
    }
    if (idCheck && pwCheck) {
        // 아이디 중복체크, 비밀 번호 확인 완료
        // controller에서 이 signal을 받으면 객체 생성
        emit signUpComplete(ui->idLineEdit->text().toStdString(), ui->pwdLineEdit->text().toStdString());
    }
}

void SignUpWidget::checkPwCheck(const QString& text) {
    // 비밀 번호 재확인 체크
    if (text.length() == 0) {
        ui->pwdCheckMessageLabel->setText("");
        pwCheck = false;
    }
    else if (ui->pwdLineEdit->text() == text) {
        setMessageLabel(ui->pwdCheckMessageLabel, tr("비밀번호가 일치 합니다."), tr("QLabel { color : green; }"));
        pwCheck = true;
    }
    else {
        setMessageLabel(ui->pwdCheckMessageLabel, tr("비밀번호가 일치하지 않습니다."), tr("QLabel { color : red; }"));
        pwCheck = false;
    }
}

void SignUpWidget::checkId() {
    // 아이디 중복 체크
    qDebug() << "아이디 중복 체크";
    QString idInput = ui->idLineEdit->text();
    if (idInput.length() < 4) {
        setMessageLabel(ui->idMessageLabel, tr("아이디는 최소 4자 이상입니다."), tr("QLabel { color : red; }"));
        return;
    }
    for (const auto& id : ids) {
        if (idInput == id) {
            idCheck = false;
            break;
        }
        else idCheck = true;
    }
    if (ids.size() == 0) idCheck = true;

    if (idCheck) {
        setMessageLabel(ui->idMessageLabel, tr("아이디를 사용할 수 있습니다."), tr("QLabel { color : green; }"));
    }
    else {
        setMessageLabel(ui->idMessageLabel, tr("아이디를 사용할 수 없습니다."), tr("QLabel { color : red; }"));
    }
}
