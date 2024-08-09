#include "signupwidget.h"
#include "ui_signupwidget.h"

SignUpWidget::SignUpWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SignUpWidget)
{
    ui->setupUi(this);
}

SignUpWidget::~SignUpWidget()
{
    delete ui;
}
