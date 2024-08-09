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
    qDebug() << "name: " << this->name << ", age: " << this->age << "인 관리자 생성\n";
}


string Manager::who_is_this()
{
    return "Manager";
}

void Manager::make_deposit()
{
    return;
}

void Manager::make_saving()
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
void Manager::show_all_account()
{
    return;
}

vector<Account*>& Manager::get_accounts()
{
    vector<Account*> v;
    return v;
}

Manager::~Manager()
{
    qDebug() << "name: " << this->name << ", age: " << this->age << "인 관리자 소멸\n";
}
