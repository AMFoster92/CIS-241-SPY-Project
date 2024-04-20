/*
*       Name:           Aaron Foster
*       Course:         CIS 241 - System Level Programming and Utilities
*       Project:        Final Project
*       File:           period.h
*       Description:    The Period structure definition file. Defines the custom data type
*                       used to store information about a period of time.                     
*/

#ifndef PERIOD_H
#define PERIOD_H

#define NUM_PERIODS_50  2281
#define NUM_PERIODS_100 2231
#define NUM_PERIODS_200 2131

// Defines the Period structure type to store the
// SpyEntry start index and end index as well as the
// average ratio, average put volume, average call volume,
// and average total volume during the period.
typedef struct
{
	int start_index;
	int end_index;
	float average_ratio;
	int average_put_volume;
	int average_call_volume;
	int average_total_volume;
} Period;

// Add information to Period structure pointed to by period and indexed by period_num.
void AddPeriod(int s_index, int e_index, float avg_r, int avg_pv, int avg_cv, int avg_tv, Period* period, int period_num);

#endif
