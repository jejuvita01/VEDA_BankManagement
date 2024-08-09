#include "managerwidget.h"
#include "ui_managerwidget.h"

ManagerWidget::ManagerWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ManagerWidget)
{
    ui->setupUi(this);
}

ManagerWidget::~ManagerWidget()
{
    delete ui;
}
