#include <iostream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

#include "saving.h"


Saving::Saving() : Saving(0, 0) {

}
Saving::Saving(int money, int duration) : Account(money), duration(duration) {
    calculate_interest();
}
Saving::Saving(int money, int duration, time_t s) : Account(money, s), duration(duration) {
    calculate_interest();
}
Saving::~Saving() {
    qDebug() << "Saving 소멸자" << endl;
}
void Saving::show_info() {
    balance += interest * (time(NULL) - startDate);
    qDebug() << "계좌 종류: " << duration << "개월 정기 예금 계좌" << endl;
    qDebug() << "계좌 생성일: " << make_time_string(startDate) << endl;
    Account::show_info();
}
void Saving::calculate_interest() {
    int year = duration / 12;
    this->interest = balance * (0.05) * year / 12;
}
bool Saving::deposit(int money) {
    return Account::deposit(money);
}
bool Saving::isExpired() {
    return (time(NULL) > startDate + duration);
}
string Saving::who_is_this() {
    return "Saving";
}
time_t Saving::get_start_date() {
    return Account::get_start_date();
}
int Saving::get_balance() {
    return Account::get_balance();
}
int Saving::get_duration() {
    return this->duration;
}
