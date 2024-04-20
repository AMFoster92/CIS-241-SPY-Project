/*
*       Name:           Aaron Foster
*       Course:         CIS 241 - System Level Programming and Utilities
*       Project:        Final Project
*       File:           spy_entry.h
*       Description:    The SpyEntry structure definition file. Defines the custom data
*						type used to store information about a SPY put/call data entry.
*/

#ifndef SPY_ENTRY_H
#define SPY_ENTRY_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_ENTRIES 2330


// Defines the SpyEntry structure type to store the
// date string, date information, put/call ratio, 
// put/call volumes, and total volume.
typedef struct
{
    char date[9];
    int week;
    int day;
    int month; 
    int year;  
    float spx_ratio;
    int spx_put_volume;
    int spx_call_volume;
    int spx_total_volume;
} SpyEntry;


// Tokenizes read-in data pointed at by line and adds it to the
// SpyEntry pointed at by data and indexed by entry.
void AddEntry(char *line, SpyEntry *data, int entry);

#endif