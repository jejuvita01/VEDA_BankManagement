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
time_t Saving::get_start_date() {
    return Account::get_start_date();
}
int Saving::get_balance() {
    return Account::get_balance();
}
int Saving::get_duration() {
    return this->duration;
}
