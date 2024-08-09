#include "mainwidget.h"
#include "ui_mainwidget.h"

class QPushButton;
class QLabel;

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{
    ui->setupUi(this);
}

Ui::MainWidget* MainWidget::getUi()
{
    return ui;
}

MainWidget::~MainWidget()
{
    delete ui;
}
