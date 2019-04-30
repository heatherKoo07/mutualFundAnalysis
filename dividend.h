//
// Created by Heather Hyunkyung Koo on 3/5/19.
//

#ifndef HW5_DIVIDEND_H
#define HW5_DIVIDEND_H

#include "date.h"
#include <iomanip>

class Dividend
{
private:
    Date date;
    float div;
public:
    Dividend(Date d) : date(d), div(0) {}
    Dividend(Date d, float f) : date(d), div(f) {}
    float get_div() const {return div;}
    Date get_date() const {return date;}

    bool operator<(const Dividend& right) const {
        return this->date < right.date;
    }

    friend std::ostream &operator << (std::ostream &, const Dividend &);
};


#endif //HW5_DIVIDEND_H
