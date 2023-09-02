#ifndef __PASTEVENTS_H__
#define __PASTEVENTS_H__
#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "sys/wait.h"
#include "sys/time.h"

void pastevents(int length, char *arguments[], char input[], char homedir[], char prevdir[], struct pr processes[], struct timeval start, struct timeval end, double timetaken, char process[], int isthethingworking);
void execute(int length, char *arguments[], char input[], char homedir[], char prevdir[], struct pr processes[], struct timeval start, struct timeval end, double timetaken, char process[], int isthethingworking);
void readpastevents(char path[]);



#endif