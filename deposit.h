#ifndef deposit_h
#define deposit_h


#include "account.h"
class Deposit : public Account {
public:
    Deposit();
    Deposit(int);
    Deposit(int, time_t);
    virtual void calculate_interest();
    virtual bool deposit(int money);
    virtual bool withdraw(int money);
    virtual time_t get_start_date();
    virtual int get_balance();
    virtual int get_duration();
    virtual ~Deposit();
};

#endif
