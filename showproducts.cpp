#include "showproducts.h"
#include "ui_showproducts.h"

ShowProducts::ShowProducts(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ShowProducts)
{
    ui->setupUi(this);
}

ShowProducts::~ShowProducts()
{
    delete ui;
}
