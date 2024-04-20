/*
*       Name:           Aaron Foster
*       Course:         CIS 241 - System Level Programming and Utilities
*       Project:        Final Project
*       File:           analysis.h
*       Description:    The analysis functions definition file. Defines the functions
*						used to analyze the SpyEntry data and calculate values for Periods.
*/

#ifndef ANALYSIS_H
#define ANALYSIS_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "spy_entry.h"
#include "period.h"

#define PUT_VOLUME		0
#define CALL_VOLUME		1
#define TOTAL_VOLUME	2
#define THRESHOLD		1.1

// Calculates moving average over the number of days defined by num_days using the SpyEntry 
// pointed at by data for the number of periods specified by num_periods. The determined 
// averages and relevant period information are then stored in a Period pointed at by periods.
float CalcAverageRatio(int num_days, int start, SpyEntry* data);

// Calculate the average put/call ratio from data over a number of days specified by 
// num_days and starting at the index specified by start.
void CalcMovingAveragePeriods(int num_days, Period* periods, SpyEntry* data, int num_periods);

// Calculate the average put/call volumes from data over a number of days specified by 
// num_days and starting at the index specified by start. The type of volume to be calculated
// whether put, call, or total volume is specified by type.
int CalcAverageVolume(int num_days, int start, SpyEntry* data, int type);

// Find periods that indicate a likely reversal using a short term moving average and a 
// long term moving average. Any periods found are recorded in the Period pointed to by
// reversal. To find periods that indicate a reversal the ratio of put volume and call volume
// is calculated. If a period has a higher put ratio than call ratio and they are both over
// the threshold, the start date is recorded. After recording a start date, if the call ratio
// is greater than the put ratio and both fall under the threshold then the end date is recorded
// and the Period is added to reversal.
void FindReversalSignal(Period* short_ma, Period* long_ma, Period* bear, SpyEntry* data, int max_index);

#endif