#include "mainwidget.h"
#include "loginwidget.h"
#include "signupwidget.h"
#include "widgetcontroller.h"
#include "showproducts.h"
#include "managerwidget.h"
#include "userwidget.h"
#include <QWidget>
#include <QObject>
#include <QMainWindow>
#include <QApplication>
#include <map>
#include <string>
#include "Person.h"
#include "user.h"

using namespace std;

WidgetController::WidgetController(QWidget* parent)
    : QMainWindow(parent)
{
    resize(400, 300);

    mainwdg = new MainWidget(this);
    lgnwdg = new LoginWidget(this);
    sgnupwdg = new SignUpWidget(this);
    userwdg = new UserWidget(this);
    mngwdg = new ManagerWidget(this);
    showwdg = new ShowProducts(this);

    mainwdg->show();
    lgnwdg->hide();
    sgnupwdg->hide();
    userwdg->hide();
    mngwdg->hide();
    showwdg->hide();


    // MainWidget

    // 1. Main -> Quit
    connect(mainwdg, &MainWidget::quit, qApp, &QApplication::quit);

    // 2. Main -> Login
    connect(mainwdg, &MainWidget::switchToLoginScreen, this, [=]() {
        mainwdg->hide();
        lgnwdg->show();
    });

    // 3. Main -> SignUp
    connect(mainwdg, &MainWidget::switchToSignUpScreen, this, [=]() {
        mainwdg->hide();
        sgnupwdg->show();
    });

    // 4. Main -> ShowProducts
    connect(mainwdg, &MainWidget::switchToShowProductScreen, this, [=]() {
        mainwdg->hide();
        showwdg->show();
    });


    // LoginWidget

    // 1. Login -> Main
    connect(lgnwdg, &LoginWidget::switchToMainScreen, this, [=]() {
        lgnwdg->hide();
        mainwdg->show();
    });

    // 2. Login -> User
    connect(lgnwdg, &LoginWidget::switchToUserScreen, this, [=](string id, Person* person) {
        userwdg->setPerson(person);
        userwdg->setId(id);
        lgnwdg->hide();
        userwdg->show();
    });

    // 3. Login -> Manager
    connect(lgnwdg, &LoginWidget::switchToManagerScreen, this, [=](string id, Person* person) {
        // mngwdg->setPerson(person);
        // mngwdg->setId(id);
        lgnwdg->hide();
        mngwdg->show();
    });


    // SignUpWidget

    // 1. SignUp -> Main
    connect(sgnupwdg, &SignUpWidget::switchToMainScreen, this, [=]() {
        sgnupwdg->hide();
        mainwdg->show();
    });

    // 2. SignUpComplete, SignUp -> Main
    connect(sgnupwdg, &SignUpWidget::signUpComplete, this, [=](string id, string pw){
        data.insert(make_pair(id, make_pair(pw, new User())));
        sgnupwdg->hide();
        mainwdg->show();
    });


    // UserWidget

    // 1. User -> Main
    connect(userwdg, &UserWidget::switchToMainScreen, this, [=]() {
        userwdg->hide();
        mainwdg->show();
    });

    // 2. Delete User, User -> Main
    connect(userwdg, &UserWidget::withdrawUser, this, [=](string id) {
        data.erase(data.find(id));
        userwdg->hide();
        mainwdg->show();
    });


    // Manager


    // ShowProducts

    // 1. Show -> Main
    connect(showwdg, &ShowProducts::switchToMainScreen, this, [=]() {
        showwdg->hide();
        mainwdg->show();
    });
}

void WidgetController::set_data(map<string, pair<string, Person*>> data)
{
    this->data = data;
}

WidgetController::~WidgetController() {}
