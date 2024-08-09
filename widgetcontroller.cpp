#include "loginwidget.h"
#include "ui_loginwidget.h"
#include "ui_mainwidget.h"
#include "mainwidget.h"
#include "widgetcontroller.h"
#include <QWidget>
#include <QObject>
#include <QMainWindow>
#include <map>
#include <string>
#include "Person.h"

using namespace std;

WidgetController::WidgetController(QWidget* parent)
    : QMainWindow(parent)
{
    mainwdg = new MainWidget(this);
    lgnwdg = new LoginWidget(this);
    setCentralWidget(mainwdg);
    lgnwdg->hide();
    Ui::MainWidget *mainUi = mainwdg->getUi();
    connect(mainUi->loginBtn, &QPushButton::clicked, this, [=] () {
        mainwdg->hide();
        lgnwdg->show();
    });
}

void WidgetController::set_data(map<string, pair<string, Person*>> data)
{
    this->data = data;
}

WidgetController::~WidgetController() {}
