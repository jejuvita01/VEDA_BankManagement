#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "deposit.h"
#include "utility.h"

Deposit::Deposit() : Deposit(0) {

}
Deposit::Deposit(int money) : Account(money) {
    calculate_interest();
}
Deposit::Deposit(int money, time_t s) : Account(money, s) {
    calculate_interest();
}
Deposit::~Deposit() {
    qDebug() << "Deposit 소멸자" << endl;
}
void Deposit::show_info() {
    balance += interest * (time(NULL) - startDate);
    qDebug() << "계좌 종류: 보통 예금 계좌" << endl;
    qDebug() << "계좌 생성일: " << make_time_string(startDate) << endl;
    Account::show_info();
}
void Deposit::calculate_interest() {
    this->interest = balance * (0.03) / 12;
}
bool Deposit::deposit(int money) {
    return Account::deposit(money);
}
bool Deposit::withdraw(int money) {
    return Account::withdraw(money);
}
string Deposit::who_is_this() {
    return "Deposit";
}
time_t Deposit::get_start_date() {
    return Account::get_start_date();
}
int Deposit::get_balance() {
    return Account::get_balance();
}
int Deposit::get_duration() {
    return 0;
}
