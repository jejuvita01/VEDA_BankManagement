#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <QPushButton>
#include <QLabel>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    connect(ui->endBtn, &QPushButton::clicked, this, [=]() { emit quit(); });
    connect(ui->loginBtn, &QPushButton::clicked, this, [=]() { emit switchToLoginScreen(); });
    connect(ui->signUpBtn, &QPushButton::clicked, this, [=]() { emit switchToSignUpScreen(); });
    connect(ui->showBtn, &QPushButton::clicked, this, [=]() { emit switchToShowProductScreen(); });
}

Ui::MainWidget* MainWidget::getUi()
{
    return ui;
}

MainWidget::~MainWidget()
{
    delete ui;
}
