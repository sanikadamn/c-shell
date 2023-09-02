#ifndef __FILES_H__
#define __FILES_H__
#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"

int dotdot(char input[], char currcopy[]);
int dot(char input[], char currcopy[]);
int tilda(char input[], char homedir[], char currcopy[]);
int directory(char input[], char currcopy[]);
int finaldirectory(char input[], char homedir[], char prevdir[], char currcopy[]);


#endif