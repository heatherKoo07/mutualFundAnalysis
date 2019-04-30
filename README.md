# mutualFundAnalysis
1. Read each of (the 2) NAV files into an unordered_set<string> and then write that container back out into a new file.  Use the output file names, VTSMXshuffled.csv & VFINXshuffled.csv. 
  
2. Produce the report shown in the sample output below using the following definitions:
The Analysis Date is the most recent date in your history data file.  
The Latest NAV is the most recent NAV in your history data file.
The Minimum for the last year represents the minimum Close in the last year.  For example, if your Analysis Date is 2/24/18, then you must use the dates between 2/25/17 and 2/24/18 (inclusive) for your analysis.  Keep in mind that 2/25/17 may not be a market day, so you may have to consider the 26th or 27th.
The Maximum for the last year will use the same rules as the Minimum for the last year.
The 50-day moving average is the average over the last 50 market days.
The 200-day moving average is the average over the last 200 market days.
The % gain over 200-Day Moving Avg is the percent gain of the Latest Close over the 200 day moving average. 
The gain over the last 3 years is the difference between the current value after applying dividends and your initial investment (use $10000).  The % gain is the gain divided by the initial investment, then expressed as a percent.  To determine the last 3 years, subtract 3 from the year of the analysis date.  For example, if the analysis date is 3/9/18, use 3/9/15 as a start date for the 3 year period.  If 3/9/15 is not a market day, use the next market day after that date.  Note, the fund must be held for at least 30 days before a dividend is paid.  

3. Compare the two mutual funds by evaluating the performance of the funds over 100 random time periods.  Dividends are reinvested.  You will determine the gain of each fund using an initial investment of $10,000 during the time period after applying the dividends awarded during the period.  Finally, you will determine the average gains for both funds over the 100 random time periods.  

Constraints
A mutual fund should be held for at least one year.  You may assume one year is 250 market days.  So, your random time period must be at least one year in duration.
A mutual fund dividend is awarded only if the fund is held at least 30 days.
