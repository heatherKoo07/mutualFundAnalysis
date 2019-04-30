//
// Created by Heather Hyunkyung Koo on 3/10/19.
//
#include "date.h"

/**~*~*
    Constructor
 *~**/
Date::Date() {
    tm y2k = {0};
    y2k.tm_year = 100;
    y2k.tm_mday = 1;
    date = mktime(&y2k);
}

/**~*~*
    Constructor with a cstring argument
 *~**/
Date::Date(const char* d) {
    tm temp = {0,0,0,0,0,0,0,0,0};
    char t[11];
    strcpy(t, d);
    char* p = strtok(t, "-");
    temp.tm_year = atoi(p) - 1900;
    p = strtok(NULL, "-");
    temp.tm_mon = atoi(p) - 1;
    p = strtok(NULL, "-");
    temp.tm_mday = atoi(p);

    date = mktime(&temp);
}

/**~*~*
    returns Date of n years ago
 *~**/
Date Date::get_n_years_ago(int n) {
    time_t d = date;
    tm* timeinfo = localtime(&d);
    timeinfo->tm_year -= n;
    timeinfo->tm_mday += 1;
    return Date(mktime(timeinfo));
}

/**~*~*
    returns Date of n years later
 *~**/
Date Date::get_n_days_later(int n) {
    time_t d = date;
    tm* timeinfo = localtime(&d);
    timeinfo->tm_mday += n;
    return Date(mktime(timeinfo));
}

/**~*~*
    returns Date of n days ago
 *~**/
Date Date::get_n_days_ago(int n) {
    time_t d = date;
    tm* timeinfo = localtime(&d);
    timeinfo->tm_mday -= n;
    return Date(mktime(timeinfo));
}

/**~*~*
    sets random dates given start and end date.
 *~**/
void Date::set_random_date(Date start_date, Date end_date) {
    date = rand() % (end_date.date - start_date.date) + start_date.date;
}

/**~*~*
    Overloads insertion operator
 *~**/
std::ostream &operator << (std::ostream &strm, const Date &obj) {
    tm* timeinfo = localtime(&obj.date);

    std::ostringstream sout;
    sout << std::setfill('0') << std::setw (2) << timeinfo->tm_mon + 1 << "/"
         << std::setfill('0') << std::setw (2) << timeinfo->tm_mday << "/" << timeinfo->tm_year + 1900;
    strm << sout.str();

    return strm;
}
