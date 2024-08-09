//
//  manager.h
//  CPP
//
//  Created by 김서현 on 8/1/24.
//

#ifndef manager_h
#define manager_h

#include "person.h"

class Manager : public Person {
public:
    Manager();
    Manager(string name, int age);
    string who_is_this();
    virtual void show_all_account();
    virtual void make_deposit();
    virtual void make_saving();
    virtual void insert_deposit(int);
    virtual void insert_saving(int, int);
    virtual void insert_deposit(int, time_t);
    virtual void insert_saving(int, int, time_t);
    virtual vector<Account*>& get_accounts();
    virtual ~Manager();
};


#endif /* manager_h */
