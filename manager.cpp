//
//  manager.cpp
//  CPP
//
//  Created by 김서현 on 8/1/24.
//

#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "manager.h"

Manager::Manager() : Person()
{

}

Manager::Manager(string name, int age) : Person(name, age)
{
}


void Manager::make_deposit(int money)
{
    return;
}

void Manager::make_saving(int money, int year)
{
    return;
}
void Manager::insert_deposit(int money) {
    return;
}
void Manager::insert_saving(int money, int duratin) {
    return ;
}
void Manager::insert_deposit(int money, time_t s) {
    return;
}
void Manager::insert_saving(int money, int duratin, time_t s) {
    return ;
}
void Manager::erase_account(int idx) {
    return;
}
vector<Account*> Manager::get_accounts()
{
    vector<Account*>* v = new vector<Account*>();
    return *v;
}

Manager::~Manager()
{
}
