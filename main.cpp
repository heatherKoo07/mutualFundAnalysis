/**
 CIS 29: Homework 5
 NAME: Heather Hyunkyung Koo
 IDE(compiler):  CLion(Clang)
 OS: Mac
 **/

#include <iostream>
#include <unordered_set>
#include <string>
#include <fstream>
#include <iomanip>

#include "date.h"
#include "mutualfund.h"
using namespace std;

void shuffleNavHistoryFile(string);
void analyze2Funds(MutualFund, MutualFund);

int main() {
    // Part 1
    string ticker1 = "VTSMX", ticker2 = "VFINX";
    shuffleNavHistoryFile(ticker1);
    shuffleNavHistoryFile(ticker2);

    // Part 2
    MutualFund vtsmx(ticker1);
    MutualFund vfinx(ticker2);
    vtsmx.report();
    vfinx.report();

    // Part 3
    analyze2Funds(vtsmx, vfinx);

    return 0;
}

/**~*~*
    Read each of (the 2) NAV files into an unordered_set<string>
    and then write that container back out into a new file
 *~**/
void shuffleNavHistoryFile(string filename) {
    string InputFile = filename + ".csv";
    string OutputFile = filename + "shuffled.csv";

    ifstream fin(InputFile);
    ofstream fout(OutputFile);

    if (!fin)
    {
        cerr << "Unable to open input file " << InputFile << endl;
        exit(1);
    }

    if (!fout) {
        cerr << "Unable to open output file " << OutputFile << endl;
        exit(2);
    }

    string line;
    getline(fin, line);
    unordered_set<string> line_set;
    cout << "Reading " << InputFile << "into an unordered_set<string>...\n";

    while (!fin.eof()) {
        getline(fin, line);
        line_set.insert(line);
    }

    cout << "Input data stored in " << line_set.bucket_count() << " buckets\n";
    cout << "Writing unordered_set<string> data into file " << OutputFile << endl << endl;

    for (auto it = line_set.begin(); it != line_set.end(); it++) {
        fout << *it << endl;
    }

    fin.close();
    fout.close();
}

/**~*~*
    Compare the two mutual funds by evaluating the performance of the funds over 100 random time periods.
    Dividends are reinvested.
 *~**/
void analyze2Funds(MutualFund m1, MutualFund m2) {
    std::cout << std::setw(10) << "Buy Date" << std::setw(15) << "Sell Date"
              << std::setw(15) << m1.getTicker() + " Value"  << std::setw(15) << m1.getTicker() + " Gain"
              << std::setw(15) << m1.getTicker() + " Value" << std::setw(15) << m1.getTicker() + " Gain"
              << std::setw(15) << m1.getTicker() + "-" + m2.getTicker() << std::endl;

    int n = 100, i = n;
    float m1_gain_total = 0, m2_gain_total = 0;
    while (i--) {
        Date buy_date, sell_date;
        m1.get_random_dates(buy_date, sell_date);

        float m1_value = m1.get_value(buy_date, sell_date);
        float m1_gain = m1.get_gain(m1_value);
        float m2_value = m2.get_value(buy_date, sell_date);
        float m2_gain = m2.get_gain(m2_value);

        std::cout << std::setw(10) << buy_date << std::setw(15) << sell_date
                  << std::setw(15) << m1_value << std::setw(15) << m1_gain
                  << std::setw(15) << m2_value << std::setw(15) << m2_gain << std::setw(15) << m1_value - m2_value << std::endl;

        m1_gain_total += m1_gain;
        m2_gain_total += m2_gain;
    }

    std::cout << "Average gain for " << m1.getTicker() << "=" << m1_gain_total / n << std::endl;
    std::cout << "Average gain for " << m2.getTicker() << "=" << m2_gain_total / n << std::endl;
    std::cout << std::endl;
}
