//
//  person.cpp
//  CPP
//
//  Created by 김서현 on 8/1/24.
//

#include <string>

using namespace std;

#include "person.h"

Person::Person()
{
    this->name = "";
    this->age = 0;
}

Person::Person(string name, int age)
{
    this->name = name;
    this->age = age;
}

void Person::set_name(string name)
{
    this->name = name;
}

void Person::set_age(int age)
{
    this->age = age;
}

string Person::get_name()
{
    return this->name;
}

int Person::get_age()
{
    return this->age;
}

Person::~Person()
{

}
