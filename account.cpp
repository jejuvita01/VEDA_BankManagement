#include <iostream>
#include <string>
#include <vector>
using namespace std;
#include "account.h"
#include "utility.h"

Account::Account() : Account(0) {}
Account::Account(int money) {
    this->balance = money;
    this->startDate = time(NULL);
}
Account::Account(int money, time_t s) {
    this->balance = money;
    this->startDate = s;
}
Account::~Account() {
    qDebug() << "Account 소멸자" << endl;
}
void Account::show_info() {
    qDebug() << "계좌 잔액: " << num_to_string_with_comma(balance) << "원" << endl;
}
bool Account::deposit(int money) {
    this->balance += money;
    qDebug() << num_to_string_with_comma(money) << "원 입금 완료" << endl;
    return true;
}
bool Account::withdraw(int money) {
    if (this->balance < money) {
        qDebug() << "잔액 부족" << endl;
        return false;
    }
    this->balance -= money;
    qDebug() << num_to_string_with_comma(money) << "원 출금 완료" << endl;
    return true;
    // try
    // {
    //   if (this->balance < money) throw new exception("잔액 부족");
    //   this->balance -= money;
    //   qDebug() << money << "원 출금 완료" << endl;
    // }
    // catch(const std::exception& e)
    // {
    //   std::cerr << e.what() << '\n';
    // }
}
time_t Account::get_start_date() {
    return this->startDate;
}
int Account::get_balance() {
    return this->balance;
}
