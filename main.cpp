#include "widgetcontroller.h"
#include "loginwidget.h"
#include "person.h"
#include "user.h"
#include "manager.h"
#include "account.h"
#include "deposit.h"
#include "saving.h"

#include <QApplication>
#include <string>
#include <map>
#include <fstream>

using namespace std;


map<string, pair<string, Person*>> sys; // id: <pw,person>
string id, pw;

void init_data()
{
    // qDebug() << "... 초기 데이터 입력중 ... \n";
    ifstream fin;
    fin.open("person_data.txt");

    int N; fin >> N;
    for (int i = 0; i < N; i++) {
        string id, pw, person_type; fin >> person_type >> id >> pw;
        string name; int age; fin >> name >> age;
        qDebug() << person_type << ' ' << id << ' ' << pw;
        if (person_type == "User") {
            qDebug() << "USER" << person_type << ' ' << id << ' ' << pw;
            sys.insert(make_pair(id, make_pair(pw, new User(name, age))));
            int account_N; fin >> account_N;
            Person* tmp = sys[id].second;
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
            sys.insert(make_pair(id, make_pair(pw, new Manager(name, age))));
        }
    }
    // qDebug() << "\n\n";
    fin.close();
}

void save_data() {
    ofstream fout;
    fout.open("output_data.txt");

    fout << sys.size() << endl;
    for (const auto& person : sys) {
        string type;
        if (dynamic_cast<User*>(person.second.second))
            type = "User";
        else if (dynamic_cast<Manager*>(person.second.second))
            type = "Manager";
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

int main(int argc, char *argv[])
{
    // sys.insert({"sungmin", {"990819", new User("박성민", 24)}});
    // sys.insert({"manager", {"000000", new Manager("매니저", 40)}});

    QApplication a(argc, argv);

    WidgetController *wdgctrl = new WidgetController();
    wdgctrl->show();
    // save_data();

    return a.exec();
}
