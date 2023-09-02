#include "../headers.h"

int callfunction(int length, char *arguments[], char input[], char homedir[], char prevdir[], struct pr processes[], struct timeval start, struct timeval end, double timetaken, char process[], int isthethingworking)
{
    char token[1000] = {};
    strcpy(token, arguments[0]);

    // printf("token: %s\n", token);

    char tokencopy[1000];
    strcpy(tokencopy, token);

    if (strncmp(token, "warp", 4) == 0 && (token[4] == ' ' || token[4] == '\n' || token[4] == '\t' || strlen(token) == 4))
    {
        char *arguments[] = {tokencopy, homedir, prevdir, "1", NULL};
        if (warp(length, arguments) == 1)
            return 1;
        // pastevents(length, arguments);
    }
    else if (strncmp(token, "peek", 4) == 0 && (token[4] == ' ' || token[4] == '\n' || token[4] == '\t' || strlen(token) == 4))
    {
        char *arguments[] = {tokencopy, homedir, prevdir, "1", NULL};
        if (peek(length, arguments) == 1)
            return 1;
        // pastevents(length, arguments);
    }
    else if (strncmp(token, "seek", 4) == 0 && (token[4] == ' ' || token[4] == '\n' || token[4] == '\t' || strlen(token) == 4))
    {
        char *arguments[] = {tokencopy, homedir, prevdir, "1", NULL};
        if (seek(length, arguments) == 1)
            return 1;
        // pastevents(length, arguments);
    }
    else if (strncmp(token, "pastevents", 10) == 0 && (token[10] == ' ' || token[10] == '\n' || token[10] == '\t' || strlen(token) == 10))
    {
        char *arguments[] = {tokencopy, homedir, prevdir, "0", NULL};
        pastevents(length, arguments, input, homedir, prevdir, processes, start, end, timetaken, process, isthethingworking);
        return 0;
    }
    else if (strncmp(token, "proclore", 8) == 0 && (token[8] == ' ' || token[8] == '\n' || token[8] == '\t' || strlen(token) == 8))
    {
        char *arguments[] = {tokencopy, homedir, prevdir, "1", NULL};
        if (proclore(length, arguments) == 1)
            return 1;
        // pastevents(length, arguments);
    }
    else
    {
        char *arguments[] = {tokencopy, homedir, prevdir, "1", NULL};
        system(token);
        // clear_token(tokencopy);
        // if(tokencopy[0] != '\0')
        // pastevents(length, arguments);
        return 1;
    }
    // check if token is a system command

    return 0;
}