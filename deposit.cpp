
using namespace std;

#include "deposit.h"

Deposit::Deposit() : Deposit(0) {

}
Deposit::Deposit(int money) : Account(money) {
    calculate_interest();
}
Deposit::Deposit(int money, time_t s) : Account(money, s) {
    calculate_interest();
}
Deposit::~Deposit() {
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
time_t Deposit::get_start_date() {
    return Account::get_start_date();
}
int Deposit::get_balance() {
    return Account::get_balance();
}
int Deposit::get_duration() {
    return 0;
}
