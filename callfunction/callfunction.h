#ifndef __CALLFUNCTION_H__
#define __CALLFUNCTION_H__
#include "string.h"
#include "unistd.h"
#include "stdio.h"

int callfunction(int length, char *arguments[], char input[], char homedir[], char prevdir[], struct pr processes[], struct timeval start, struct timeval end, double timetaken, char process[], int isthethingworking);
#endif