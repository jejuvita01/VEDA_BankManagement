#include "widgetcontroller.h"
#include "loginwidget.h"
#include "person.h"
#include "user.h"
#include "manager.h"

#include <QApplication>
#include <string>
#include <map>
//#include <fstream>

using namespace std;


map<string, pair<string, Person*>> sys; // id: <pw,person>
string id, pw;


// void description(void)
// {
//     qDebug() << "\n\nVEDA 은행에는 다음과 같은 상품이 있습니다.\n";
//     qDebug() << "1. 보통예금: 10,000만원 한도, 연 3%(단리)\n";
//     qDebug() << "2. 정기예금: 1년 만기, 최대 5,000만원 입금, 연 5%(단리)\n";
//     qDebug() << "많은 이용 바랍니다.\n\n\n";
// }



// void init_data()
// {
//     // qDebug() << "... 초기 데이터 입력중 ... \n";
//     ifstream fin;
//     fin.open("person_data.txt");

//     int N; fin >> N;
//     for (int i = 0; i < N; i++) {
//         string id, pw, person_type; fin >> person_type >> id >> pw;
//         string name; int age; fin >> name >> age;

//         if (person_type == "User") {
//             sys.insert(make_pair(id, make_pair(pw, new User(name, age))));
//             int account_N; fin >> account_N;
//             Person* tmp = sys[id].second;
//             for (int j = 0; j < account_N; j++) {
//                 string account_type; int s; int balance;
//                 fin >> account_type >> s >> balance;
//                 if (account_type == "Deposit") {
//                     tmp->insert_deposit(balance, s);
//                 }
//                 else if (account_type == "Saving") {
//                     int duration; fin >> duration;
//                     tmp->insert_saving(balance, duration, s);
//                 }
//             }
//         }
//         else if (person_type == "Manager") {
//             sys.insert(make_pair(id, make_pair(pw, new Manager(name, age))));
//         }
//     }
//     // qDebug() << "\n\n";
//     fin.close();
// }

// void save_data() {
//     ofstream fout;
//     fout.open("person_data.txt");

//     fout << sys.size() << endl;
//     for (const auto& person : sys) {
//         const string& type = person.second.second->who_is_this();
//         fout << type << " " << person.first << " " << person.second.first << " " << endl;
//         fout << person.second.second->get_name() << " " << person.second.second->get_age() << endl;
//         if (type == "User") {
//             const auto& accounts = person.second.second->get_accounts();
//             fout << accounts.size() << endl;
//             for (const auto& account : accounts) {
//                 const string& account_type = account->who_is_this();
//                 fout << account_type << " " << account->get_start_date() << " " << account->get_balance() << " ";
//                 if (account_type == "Saving") fout << account->get_duration() << endl;
//                 else fout << endl;
//             }
//         }

//     }
//     fout.close();
// }

int main(int argc, char *argv[])
{
    sys.insert({"sungmin", {"990819", new User("박성민", 24)}});
    sys.insert({"manager", {"000000", new Manager("매니저", 40)}});
    //init_data();
    //save_data();

    QApplication a(argc, argv);
    // MainWindow w;
    // w.show();

    WidgetController *wdgctrl = new WidgetController();
    wdgctrl->set_data(sys);
    wdgctrl->show();

    return a.exec();
}
