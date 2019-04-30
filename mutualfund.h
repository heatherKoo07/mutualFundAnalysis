//
// Created by Heather Hyunkyung Koo on 3/5/19.
//

#ifndef HW5_MUTUALFUND_H
#define HW5_MUTUALFUND_H

#include "date.h"
#include "dividend.h"
#include <string>
#include <map>
#include <set>
#include <fstream>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>

class MutualFund
{
private:
    std::string ticker;
    Date oldestDate;      // optional
    Date newestDate;      // optional
    float newestNav;      // optional
    std::map<Date, float> navHistory;
    std::set<Dividend> divHistory;

public:
    const int initialInvest = 10000;
    const int MarketdaysPerYear = 250;
    const std::string OutputFile_div = "dividend_detail.txt";

    MutualFund(std::string t);
    void erase_past_dividend_file();
    void report();
    std::string getTicker() { return ticker;}
    float getMinLastYear();
    float getMaxLastYear();
    float movingAverage(int n);
    float getThreeYearReturn();
    void get_random_dates(Date& start_date, Date& end_date);
    float get_value(Date start_date, Date end_date);
    float get_gain(float value) { return value - initialInvest; }
    float write_to_dividend_detail(Date, Date);
};

#endif //HW5_MUTUALFUND_H
