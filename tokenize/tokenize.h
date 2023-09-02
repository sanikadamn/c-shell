#ifndef __TOKENIZE_H__
#define __TOKENIZE_H__
#include "string.h"

int tokenize(char input[], char homedir[], char prevdir[], struct pr processes[], struct timeval start, struct timeval end, double timetaken, char process[], int isthethingworking);

#endif