#include "account.h"
using namespace std;

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
}
bool Account::deposit(int money) {
    if (this->balance + money > MAX_BALANCE) {
        return false;
    }
    this->balance += money;
    return true;
}
bool Account::withdraw(int money) {
    if (this->balance < money) {
        return false;
    }
    this->balance -= money;
    return true;
}
time_t Account::get_start_date() {
    return this->startDate;
}
int Account::get_balance() {
    return this->balance;
}
