#include "../headers.h"

int tokenize(char input[], char homedir[], char prevdir[], struct pr processes[], struct timeval start, struct timeval end, double timetaken, char process[], int isthethingworking)
{
    char *saveptr = NULL;
    char *token = __strtok_r(input, ";", &saveptr);
    while (token != NULL)
    {
        remove_leading_whitespaces(token);
        isthethingworking = (fgbg(token, homedir, prevdir, processes, start, end, timetaken, process, isthethingworking, saveptr) && 1);
        // call fgbg
        token = __strtok_r(NULL, ";", &saveptr);
    }
    return isthethingworking;
}
