//
//  user.cpp
//  CPP
//
//  Created by 김서현 on 8/1/24.
//

#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "user.h"
class Deposit;

User::User() : Person()
{

}

User::User(string name, int age) : Person(name, age)
{
    qDebug() << "name: " << this->name << ", age: " << this->age << "인 사용자 생성\n";
}

void User::make_deposit()
{
    qDebug() << "보통예금 - 입금할 액수를 입력하세요: \n";
    int money;
    cin >> money;
    insert_deposit(money);
    qDebug() << "보통예금이 생성되었습니다. \n";
    qDebug() << "보통예금 잔액: " << money << '\n';
}

void User::make_saving()
{
    int money, year;
    qDebug() << "정기예금 - 입금할 액수를 입력하세요: \n";
    cin >> money;
    qDebug() << "정기예금 - 입금할 년 수를 입력하세요: \n";
    cin >> year;
    insert_saving(money, year * 12);
    qDebug() << "정기예금이 생성되었습니다.\n";
    qDebug() << "정기예금 잔액: " << money << ", 기간: " << year << "년\n";
}
void User::insert_deposit(int money) {
    this->accounts.push_back(new Deposit(money));
}

void User::insert_saving(int money, int duration) {
    this->accounts.push_back(new Saving(money, duration));
}

void User::insert_deposit(int money, time_t s) {
    this->accounts.push_back(new Deposit(money, s));
}

void User::insert_saving(int money, int duration, time_t s) {
    this->accounts.push_back(new Saving(money, duration, s));
}

void User::show_all_account() {
    if (accounts.empty()) {
        qDebug() << "계좌가 없습니다." << endl;
        return;
    }
    int idx = 1;
    for (const auto& account : accounts) {
        qDebug() << idx << "번 계좌: ";
        account->show_info();
        idx++;
    }
}

string User::who_is_this()
{
    return "User";
}

vector<Account*>& User::get_accounts()
{
    return this->accounts;
}

User::~User()
{
    for (const auto& account : accounts) {
        delete account;
    }
    qDebug() << "name: " << this->name << ", age: " << this->age << "인 사용자 소멸\n";
}
