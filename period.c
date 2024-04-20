/*
*       Name:           Aaron Foster
*       Course:         CIS 241 - System Level Programming and Utilities
*       Project:        Final Project
*       File:           period.c
*       Description:    The Period structure implementation file. Defines the custom data
*						type used to store information about a period of time.
*/

#include "period.h"

// Add information to Period structure pointed to by period and indexed by period_num.
void AddPeriod(int s_index, int e_index, float avg_r, int avg_pv, int avg_cv, int avg_tv, Period* period, int period_num)
{
	period[period_num].start_index = s_index;
	period[period_num].end_index = e_index;
	period[period_num].average_ratio = avg_r;
	period[period_num].average_put_volume = avg_pv;
	period[period_num].average_call_volume = avg_cv;
	period[period_num].average_total_volume = avg_tv;
}
