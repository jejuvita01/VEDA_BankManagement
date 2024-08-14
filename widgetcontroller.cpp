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
#include <fstream>
#include "Person.h"
#include "user.h"
#include "manager.h"
#include "account.h"
#include "deposit.h"
#include "saving.h"

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
    connect(mainwdg, &MainWidget::quit, qApp, [=]() {
        save_data();
        qApp->quit();
    });

    // 2. Main -> Login
    connect(mainwdg, &MainWidget::switchToLoginScreen, this, [=]() {
        mainwdg->hide();
        lgnwdg->setData(data);
        lgnwdg->show();
    });

    // 3. Main -> SignUp
    connect(mainwdg, &MainWidget::switchToSignUpScreen, this, [=]() {
        mainwdg->hide();
        sgnupwdg->insertData(data);
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
        mngwdg->setPerson(person);
        mngwdg->setId(id);
        mngwdg->setData(data);
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
        data.insert(make_pair(id, make_pair(pw, new User("name", 10))));
        sgnupwdg->insertData(data);
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

    // 1. Manager -> Main
    connect(mngwdg, &ManagerWidget::switchTomainScreen, this, [=]() {
        mngwdg->setData(data);
        mngwdg->hide();
        mainwdg->show();
    });

    // 2. Delete Manager, Manager -> Main
    connect(mngwdg, &ManagerWidget::withdrawManager, this, [=](string id) {
        data.erase(data.find(id));
        mngwdg->hide();
        mainwdg->show();
    });

    // 3. Delete User
    connect(mngwdg, &ManagerWidget::withdrawUser, this, [=](string id) {
        data.erase(data.find(id));
        mngwdg->setData(data);
    });

    // ShowProducts

    // 1. Show -> Main
    connect(showwdg, &ShowProducts::switchToMainScreen, this, [=]() {
        showwdg->hide();
        mainwdg->show();
    });

    init_data();
}

void WidgetController::set_data(map<string, pair<string, Person*>> data)
{
    this->data = data;
}

void WidgetController::init_data()
{
    // qDebug() << "... 초기 데이터 입력중 ... \n";
    ifstream fin;
    fin.open(PATH);

    int N; fin >> N;
    for (int i = 0; i < N; i++) {
        string id, pw, person_type; fin >> person_type >> id >> pw;
        string name; int age; fin >> name >> age;
        qDebug() << person_type << ' ' << id << ' ' << pw;
        if (person_type == "User") {
            qDebug() << "USER" << person_type << ' ' << id << ' ' << pw;
            data.insert(make_pair(id, make_pair(pw, new User(name, age))));
            int account_N; fin >> account_N;
            Person* tmp = data[id].second;
            for (int j = 0; j < account_N; j++) {
                string account_type; int s; int balance;
                fin >> account_type >> s >> balance;
                if (account_type == "Deposit") {
                    tmp->insert_deposit(balance, s);
                }
                else if (account_type == "Saving") {
                    int duration; fin >> duration;
                    tmp->insert_saving(balance, duration, s);
                }
            }
        }
        else if (person_type == "Manager") {
            qDebug() << "MANAGER" << person_type << ' ' << id << ' ' << pw;
            data.insert(make_pair(id, make_pair(pw, new Manager(name, age))));
        }
    }
    // qDebug() << "\n\n";
    fin.close();
}

void WidgetController::save_data()
{
    ofstream fout;
    fout.open(PATH);

    fout << data.size() << endl;
    for (const auto& person : data) {
        string type;
        if (dynamic_cast<User*>(person.second.second))
            type = "User";
        else if (dynamic_cast<Manager*>(person.second.second))
            type = "Manager";
        qDebug() << type << person.first << person.second.first;
        fout << type << " " << person.first << " " << person.second.first << " " << endl;
        fout << person.second.second->get_name() << " " << person.second.second->get_age() << endl;
        if (type == "User") {
            const auto& accounts = person.second.second->get_accounts();
            fout << accounts.size() << endl;
            for (const auto& account : accounts) {
                string account_type;
                if (dynamic_cast<Deposit*>(account))
                    account_type = "Deposit";
                else if (dynamic_cast<Saving*>(account))
                    account_type = "Saving";
                fout << account_type << " " << account->get_start_date() << " " << account->get_balance() << " ";
                if (account_type == "Saving") fout << account->get_duration() << endl;
                else fout << endl;
            }
        }

    }
    fout.close();
}

WidgetController::~WidgetController() {}
