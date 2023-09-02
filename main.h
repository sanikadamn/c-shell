#ifndef __MAIN_H__
#define __MAIN_H__
#include "string.h"
#include "sys/time.h"
#include "sys/wait.h"


// void remove_leading_whitespaces(char input[]);
// void callfunction(char token[], char homedir[], char prevdir[]);
// int main();
int main(int argc, char *argv[]);
// void checkbgprocess(struct process processes[]);

// make a struct that stores the process id and the process name
// make a global array of that struct
struct pr
{
    pid_t pid;
    int index;
    char name[1000];
};
extern struct pr processes[1000];


#endif