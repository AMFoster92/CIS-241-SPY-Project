/*
*       Name:           Aaron Foster
*       Course:         CIS 241 - System Level Programming and Utilities
*       Project:        Final Project
*       File:           spy_entry.c
*       Description:    The SpyEntry structure implementation file. Defines the custom data
*						type used to store information about a SPY put/call data entry.
*/

#include "spy_entry.h"

// Tokenizes read-in data pointed at by line and adds it to the
// SpyEntry pointed at by data and indexed by entry.
void AddEntry(char *line, SpyEntry *data, int entry)
{
    char *token;
    char num[10];
    char date[11];

    token = strtok(line, ",");
    strcpy(data[entry].date, token);
    strcpy(date, data[entry].date);

    token = strtok(NULL, ",");
    strcpy(num, token);
    data[entry].spx_ratio = (float)(atof(num));

    token = strtok(NULL, ",");
    strcpy(num, token);
    data[entry].spx_put_volume = atoi(num);

    token = strtok(NULL, ",");
    strcpy(num, token);
    data[entry].spx_call_volume = atoi(num);

    token = strtok(NULL, ",");
    strcpy(num, token);
    data[entry].spx_total_volume = atoi(num);

    token = strtok(date, "/");
    strcpy(num, token);
    data[entry].month = atoi(num);

    token = strtok(NULL, "/");
    strcpy(num, token);
    data[entry].day = atoi(num);

    token = strtok(NULL, "/");
    strcpy(num, token);
    data[entry].year = atoi(num);

    if (entry > 0)
    {
        if (data[entry].day - data[entry - 1].day > 1)
        {
            data[entry].week = data[entry - 1].week + 1;
        }
        else
        {
            data[entry].week = data[entry - 1].week;
        }
    }
    else
    {
        data[entry].week = 1;
    }
}
