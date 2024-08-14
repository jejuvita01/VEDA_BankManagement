#include "showproducts.h"
#include "ui_showproducts.h"

ShowProducts::ShowProducts(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ShowProducts)
{
    ui->setupUi(this);
    connect(ui->backBtn, &QPushButton::clicked, this, &ShowProducts::switchToMainScreen);
}

ShowProducts::~ShowProducts()
{
    delete ui;
}
