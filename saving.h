#ifndef saving_h
#define saving_h

#include "account.h"
class Saving : public Account {
    int duration;
public:
    Saving();
    Saving(int, int);
    Saving(int, int, time_t);
    virtual void show_info();
    virtual void calculate_interest();
    virtual bool deposit(int money);
    virtual bool isExpired();
    virtual string who_is_this();
    virtual time_t get_start_date();
    virtual int get_balance();
    virtual int get_duration();
    virtual ~Saving();
};

#endif
