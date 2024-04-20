/*
*       Name:           Aaron Foster
*       Course:         CIS 241 - System Level Programming and Utilities
*       Project:        Final Project
*       File:           analysis.c
*       Description:    The analysis functions implementation file. Implements the functions
*						used to analyze the SpyEntry data and calculate values for Periods.
*/

#include "analysis.h"

// Calculates moving average over the number of days defined by num_days using the SpyEntry 
// pointed at by data for the number of periods specified by num_periods. The determined 
// averages and relevant period information are then stored in a Period pointed at by periods.
void CalcMovingAveragePeriods(int num_days, Period* periods, SpyEntry* data, int num_periods)
{
    float sum = 0.0;
    float average = 0.0;
    int end = 0;

    for (int start = 0; start < num_periods; start++)
    {
        end = start + num_days - 1;

        AddPeriod(start, end, CalcAverageRatio(num_days, start, data),
            CalcAverageVolume(num_days, start, data, PUT_VOLUME),
            CalcAverageVolume(num_days, start, data, CALL_VOLUME),
            CalcAverageVolume(num_days, start, data, TOTAL_VOLUME), periods, start);
    }
}


// Calculate the average put/call ratio from data over a number of days specified by 
// num_days and starting at the index specified by start.
float CalcAverageRatio(int num_days, int start, SpyEntry* data)
{
    float sum = 0.0;
    float average = 0.0;

    for (int i = 0; i < num_days; i++)
    {
        sum += data[start + i].spx_ratio;
    }

    average = sum / num_days;

    return average;
}


// Calculate the average put/call volumes from data over a number of days specified by 
// num_days and starting at the index specified by start. The type of volume to be calculated
// whether put, call, or total volume is specified by type.
int CalcAverageVolume(int num_days, int start, SpyEntry* data, int type)
{
    long long sum = 0;
    int average = 0;

    for (int i = 0; i < num_days; i++)
    {
        if (type == PUT_VOLUME)
        {
            sum += data[start + i].spx_put_volume;
        }
        else if (type == CALL_VOLUME)
        {
            sum += data[start + i].spx_call_volume;
        }
        else
        {
            sum += data[start + i].spx_total_volume;
        }

    }

    average = (int)(sum / num_days);

    return average;
}


// Find periods that indicate a likely reversal using a short term moving average and a 
// long term moving average. Any periods found are recorded in the Period pointed to by
// reversal. To find periods that indicate a reversal the ratio of put volume and call volume
// is calculated. If a period has a higher put ratio than call ratio and they are both over
// the threshold, the start date is recorded. After recording a start date, if the call ratio
// is greater than the put ratio and both fall under the threshold then the end date is recorded
// and the Period is added to reversal.
void FindReversalSignal(Period* short_ma, Period* long_ma, Period* reversal, SpyEntry* data, int max_index)
{
    int s_index = 0;
    int l_index = 0;
    int b_index = 0;
    int start_index = 0;
    int end_index = 0;
    int new_period = 0;
    float put_ratio = 0.0;
    float call_ratio = 0.0;
    int num_days = 0;
    int short_greater_long = 0;

    while (l_index < max_index)
    {
        while (short_ma[s_index].end_index != long_ma[l_index].end_index)
        {
            s_index++;
        }

        put_ratio = (float)(short_ma[s_index].average_put_volume) / long_ma[l_index].average_put_volume;
        call_ratio = (float)(short_ma[s_index].average_call_volume) / long_ma[l_index].average_call_volume;


        if ((put_ratio > call_ratio) && (put_ratio > THRESHOLD) && (call_ratio > THRESHOLD) && !new_period)
        {
            start_index = short_ma[s_index].end_index;
            new_period = 1;
        }

        if ((put_ratio < call_ratio) && (put_ratio < THRESHOLD) && (call_ratio < THRESHOLD) && new_period)
        {
            end_index = short_ma[s_index].end_index;
            num_days = end_index - start_index;

            AddPeriod(start_index, end_index, CalcAverageRatio(num_days, start_index, data),
                CalcAverageVolume(num_days, start_index, data, PUT_VOLUME),
                CalcAverageVolume(num_days, start_index, data, CALL_VOLUME),
                CalcAverageVolume(num_days, start_index, data, TOTAL_VOLUME), reversal, b_index);

            b_index++;

            new_period = 0;
        }

        s_index++;
        l_index++;
    }
    
}