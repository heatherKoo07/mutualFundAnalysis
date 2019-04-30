//
// Created by Heather Hyunkyung Koo on 3/10/19.
//

#include "mutualfund.h"

/**~*~*
    Constructor with a string argument
 *~**/
MutualFund::MutualFund(std::string t) : ticker(t) {
    srand (time(NULL));
    erase_past_dividend_file();

    std::string InputFile_shuffle = ticker + "shuffled.csv";
    std::string InputFile_div = ticker + "div.csv";
    std::string OutputFile_shuffle = ticker + "nav.txt";
    std::string OutputFile_div = ticker + "div.txt";

    std::ifstream fin_shuffle(InputFile_shuffle);
    std::ifstream fin_div(InputFile_div);
    std::ofstream fout_shuffle(OutputFile_shuffle);
    std::ofstream fout_div(OutputFile_div);

    if (!fin_shuffle)
    {
        std::cerr << "Unable to open input file " << InputFile_shuffle << std::endl;
        exit(1);
    }

    if (!fin_div)
    {
        std::cerr << "Unable to open input file " << InputFile_div << std::endl;
        exit(2);
    }

    if (!fout_shuffle)
    {
        std::cerr << "Unable to open output file " << OutputFile_shuffle << std::endl;
        exit(3);
    }

    if (!fout_div)
    {
        std::cerr << "Unable to open output file " << OutputFile_div << std::endl;
        exit(4);
    }

    // read in the shuffled NAV file into the navHistory member of each class.
    std::string field;
    int record_cnt = 0;
    while (getline(fin_shuffle, field, ',')) {
        if (field[0] == '\n') field = field.substr(1);
        Date date(field.c_str());
        // Parse the NAV input files using comma (4th and 5th) locations, not absolute positions, for the NAV values
        int field_count = 4;
        while (field_count--) {
            getline(fin_shuffle, field, ',');
        }
        float nav = stof(field);
        navHistory[date] = nav;
        getline(fin_shuffle, field);
        record_cnt++;
    }
    auto it_oldest = navHistory.begin();
    auto it_newest = navHistory.rbegin();
    oldestDate = it_oldest-> first;
    newestDate = it_newest->first;
    newestNav = it_newest->second;

    std::cout << "Reading file " << InputFile_shuffle << "...\n";
    std::cout << record_cnt << " records read\n\n";

    // read in the dividend file into the divHistory member of each class.
    record_cnt = 0;
    getline(fin_div, field);
    while (getline(fin_div, field, ',')) {
        Date date(field.c_str());
        getline(fin_div, field);
        float d = stof(field);
        Dividend div(date, d);
        divHistory.insert(div);
        record_cnt++;
    }

    std::cout << "Reading file " << InputFile_div << "...\n";
    std::cout << record_cnt << " records read\n\n";

    std::cout << "Writing NAV history data into file " << OutputFile_shuffle << "... done\n";
    std::cout << "Writing dividend history data into file " << OutputFile_div << "... done\n\n";

    // write out the contents of navHistory map into a file using the name, VTSMXnav.txt or VFINXnav.txt.
    for (auto it = navHistory.begin(); it != navHistory.end(); it++) {
        fout_shuffle << it->first << "\t" << std::setprecision(2) << std::fixed << it->second << std::endl;
    }

    // write out the contents of divHistory set into a file using the name, VTSMXdiv.txt or VFINXdiv.txt.
    for (auto it = divHistory.begin(); it != divHistory.end(); it++) {
        fout_div << std::setprecision(2) << std::fixed << *it << std::endl;
    }

    fin_shuffle.close();
    fout_shuffle.close();
    fin_div.close();
    fout_div.close();
}

/**~*~*
    Clears out the past dividend output file.
 *~**/
void MutualFund::erase_past_dividend_file() {
    std::ofstream fout(OutputFile_div);
    if (!fout) {
        std::cerr << "Unable to open output text file " << OutputFile_div << std::endl;
        exit(101);
    }
    fout.close();
}

/**~*~*
    The Minimum for the last year represents the minimum Close in the last year.
 *~**/
float MutualFund::getMinLastYear() {
    auto itlow = navHistory.lower_bound(newestDate.get_n_years_ago(1));
    float min = newestNav;
    auto it = itlow;
    while (it != navHistory.end()) {
        if (it->second < min) {
            min = it->second;
        }
        it++;
    }
    return min;
}

/**~*~*
    The Maximum for the last year represents the maximum Close in the last year.
 *~**/
float MutualFund::getMaxLastYear() {
    auto itlow = navHistory.lower_bound(newestDate.get_n_years_ago(1));
    float max = newestNav;
    auto it = itlow;
    while (it != navHistory.end()) {
        if (it->second > max) {
            max = it->second;
        }
        it++;
    }
    return max;
}

/**~*~*
    returns the average over the last n market days.
 *~**/
float MutualFund::movingAverage(int n) {
    int i = n;
    float total = 0;
    auto it = navHistory.rbegin();
    while (i--) {
        total += it->second;
        it++;
    }
    return total / n;
}

/**~*~*
    returns % difference between the current value after applying dividends
    and your initial investment (use $10000).
 *~**/
float MutualFund::getThreeYearReturn() {
    Date three_years_ago = newestDate.get_date().get_n_years_ago(3).get_n_days_ago(1);
    return get_gain(get_value(three_years_ago, newestDate)) / initialInvest * 100;
}

/**~*~*
    get random start and end dates
    whose time period must be at least one year(250 market days) in duration
 *~**/
void MutualFund::get_random_dates(Date& rand_start_date, Date& rand_end_date) {
    int rand_len = rand() % (navHistory.size()-MarketdaysPerYear) + MarketdaysPerYear;
    rand_start_date.set_random_date(oldestDate, newestDate.get_n_days_ago(rand_len));
    rand_end_date = rand_start_date.get_n_days_later(rand_len);
}

/**~*~*
    get the value of each fund using an initial investment of $10,000
    during the time period after applying the dividends awarded during the period.
 *~**/
float MutualFund::get_value( Date start_date, Date end_date) {
    float sh_owned = write_to_dividend_detail(Date(start_date), Date(end_date));
    return sh_owned * navHistory.lower_bound(end_date)->second;
}

/**~*~*
     write out a file containing dividend detail information
     for each of given time periods.
 *~**/
float MutualFund::write_to_dividend_detail(Date start_date, Date end_date) {
    std::ofstream fout(OutputFile_div, std::ofstream::app);
    float final_sh_owned;
    if (!fout)
    {
        std::cerr << "Unable to open output file " << OutputFile_div << std::endl;
        exit(4);
    }
    fout << "Dividends for " << ticker << ": " << start_date << "-" << end_date << std::endl;
    fout << std::left << std::setw(10) << "Date" << std::right << std::setw(10) << "Dividend" << std::setw(10) << "Shares"
         << std::setw(10) << "Div Amt" << std::setw(10) << "Sh Price" << std::setw(10) << "Purchased"
         << std::setw(14) << "New Sh Owned" << std::endl;

    auto itlow = navHistory.lower_bound(start_date);
    float num_of_stocks = initialInvest / itlow->second;
    Date start_date_market = itlow->first;
    for (auto it = divHistory.lower_bound(start_date_market.get_n_days_later(30)); it != divHistory.upper_bound(end_date); it++) {
        Date d = it->get_date();
        float dividend = it->get_div();
        float div_amt = dividend * num_of_stocks;
        float share_price = navHistory.find(it->get_date())->second;
        float purchased = div_amt / share_price;
        float new_sh_owned = num_of_stocks + purchased;

        fout << std::setw(10) << std::setprecision(3) << std::fixed << d
             << std::setw(10) << dividend << std::setw(10) << num_of_stocks
             << std::setw(10) << std::setprecision(2) << div_amt << std::setw(10) << share_price
             << std::setw(10) << std::setprecision(3) << purchased << std::setw(14) << new_sh_owned << std::endl;

        num_of_stocks = new_sh_owned;
    }
    final_sh_owned = num_of_stocks;

    fout << std::endl;
    fout.close();
    return final_sh_owned;
}

/**~*~*
    prints out the report of the fund
 *~**/
void MutualFund::report() {
    std::cout << "Fund: " << ticker << std::endl
              << "Analysis Date: " << newestDate << std::endl
              << "Latest NAV: $" << std::setprecision(2) << std::fixed << newestNav << std::endl
              << "Minimum for the last year = $" << getMinLastYear() << std::endl
              << "Maximum for the last year = $" << getMaxLastYear() << std::endl
              << "50 day moving average = $" << movingAverage(50) << std::endl
              << "200 day moving average = $" << movingAverage(200) << std::endl
              << "% gain over 200 Day Moving Avg: " << (newestNav - movingAverage(200)) / movingAverage(200) * 100 << "%" << std::endl
              << "% return over the last 3 years: " << getThreeYearReturn() << "%" << std::endl << std::endl;
}
