//
//  user.cpp
//  CPP
//
//  Created by 김서현 on 8/1/24.
//

#include "deposit.h"
#include "saving.h"

#include <string>
#include <vector>

using namespace std;

#include "user.h"

User::User() : Person()
{

}

User::User(string name, int age) : Person(name, age)
{
}

void User::make_deposit(int money)
{
    insert_deposit(money);
}

void User::make_saving(int money, int year)
{
    insert_saving(money, year * 12);
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
void User::erase_account(int idx) {
    this->accounts.erase(accounts.begin() + idx);
}
vector<Account*> User::get_accounts()
{
    return this->accounts;
}

User::~User()
{
    for (const auto& account : accounts) {
        delete account;
    }
}
