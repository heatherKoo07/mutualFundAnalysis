//
// Created by Heather Hyunkyung Koo on 3/5/19.
//

#ifndef HW5_DATE_H
#define HW5_DATE_H

#include <ctime>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <iomanip>

class Date
{
private:
    time_t date;
public:
    Date();
    Date(const Date&) = default;
    Date(const char*);
    Date(time_t t) {date = t;}  // Date in time_t format

    Date get_n_years_ago(int n);
    Date get_n_days_later(int n);
    Date get_n_days_ago(int n);
    Date get_date() const { return date;}
    void set_random_date(Date start_date, Date end_date);

    bool operator<(const Date &right) const {
        return this->date < right.date;
    }

    friend std::ostream &operator << (std::ostream &, const Date &);
};

#endif //HW5_DATE_H
