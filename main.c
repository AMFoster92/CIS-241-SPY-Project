/* 
*       Name:           Aaron Foster
*       Course:         CIS 241 - System Level Programming and Utilities     
*       Project:        Final Project
*       File:           main.c
*       Description:    This program analyzes an excel file containing put/call data    
*                       between mid-2010 to late 2019. The analysis looks for periods
*                       that indicate an upwards reversal within the months following.
*                       The overall trend of the data with respect to the put/call ratio
*                       is also determined.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "spy_entry.h"
#include "period.h"
#include "analysis.h"


int main(void)
{
    // Variables used to read data from file
    FILE *fp;
    char line[255];
    int cur_line = 0;

    // Array to store data from file
    SpyEntry data[NUM_ENTRIES];

    // Puts moving averages
    Period ma_50[NUM_PERIODS_50];
    Period ma_100[NUM_PERIODS_100];
    Period ma_200[NUM_PERIODS_200];

    // Market periods
    Period market_51[NUM_PERIODS_100]; // 50-Day / 100-Day MA
    Period market_52[NUM_PERIODS_200]; // 50-Day / 200-Day MA

    // Put/Call Ratio Average of SPY
    float avg_ratio = 0.0;

    // Open csv file
    fp = fopen("spxpc.csv", "r");

    fseek(fp, 357 + 81, SEEK_SET);

    // Read csv file into data array
    while (!feof(fp))
    {
        fgets(line, 255, (FILE *)fp);
        AddEntry(line, data, cur_line);
        cur_line++;
    }

    // Close csv file
    fclose(fp);

    // Calc average ratio
    avg_ratio = CalcAverageRatio(NUM_ENTRIES, 0, data);

    // Calculate the 50-day, 100-day, and 200-day moving averages
    CalcMovingAveragePeriods(50, ma_50, data, NUM_PERIODS_50);
    CalcMovingAveragePeriods(100, ma_100, data, NUM_PERIODS_100);
    CalcMovingAveragePeriods(200, ma_200, data, NUM_PERIODS_200);

    // Compare 50 day MAs and 200 day MAs to find drops
    FindReversalSignal(ma_50, ma_100, market_51, data, NUM_PERIODS_100);
    FindReversalSignal(ma_50, ma_200, market_52, data, NUM_PERIODS_200);

    // Print Average Ratio
    printf("Overall Average Put/Call Ratio: %0.2f\n\n", avg_ratio);

    // Open results file
    fp = fopen("results.csv", "w");

    // Print Reversal Periods to Console and Results File
    printf("Reversal periods found comparing 50-day and 100-day Moving Averages\n");
    printf("%12s\t%12s\n", "Start/Buy-In", "End/Hold");
    fprintf(fp,"Reversal periods found comparing 50-day and 100-day Moving Averages\n");
    fprintf(fp, "Start/Buy-In, End/Hold\n");
    for (int i = 0; i < NUM_PERIODS_100; i++)
    {
        if (market_51[i].start_index > 0)
        {
            printf("%12s\t%12s\n", data[market_51[i].start_index].date, data[market_51[i].end_index].date);
            fprintf(fp, "%s, %s\n", data[market_51[i].start_index].date, data[market_51[i].end_index].date);
        }
    }

    printf("\n\n\n\n");
    fprintf(fp, "\n\n\n");

    printf("Reversal periods found comparing 50-day and 200-day Moving Averages\n");
    printf("%12s\t%12s\n", "Start/Buy-In", "End/Hold");
    fprintf(fp, "Reversal periods found comparing 50 - day and 200 - day Moving Averages\n");
    fprintf(fp, "Start/Buy-In, End/Hold\n");
    for (int i = 0; i < NUM_PERIODS_200; i++)
    {
        if (market_52[i].start_index > 0)
        {
            printf("%12s\t%12s\n", data[market_52[i].start_index].date, data[market_52[i].end_index].date);
            fprintf(fp, "%s, %s\n", data[market_52[i].start_index].date, data[market_52[i].end_index].date);
        }
    }

    // Close results file
    fclose(fp);

    return 0;
}
