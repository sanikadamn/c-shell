#include "../headers.h"

int warp(int length, char *arguments[])
{
    char input[1000] = {}, homedir[1000] = {}, prevdir[1000] = {};
    strcpy(input, arguments[0]);
    strcpy(homedir, arguments[1]);
    strcpy(prevdir, arguments[2]);

    char* outer_saveptr = NULL;
    char *token = __strtok_r(input, " \t", &outer_saveptr);

    token = __strtok_r(NULL, " \t", &outer_saveptr);
    clear_token(token);
    if (token == NULL)
    {
        chdir(homedir);
        return 1;
    }
    if (strlen(token) == 0)
    {
        chdir(homedir);
        return 1;
    }
    while (token != NULL && strcmp(token, "\n") != 0)
    {
        char dir[1000], currdir[1000];
        strcpy(dir, prevdir);
        if (getcwd(currdir, sizeof(currdir)) == NULL)
        {
            perror("getcwd");
            return 0;
        }
        char currcopy[1000];
        strcpy(currcopy, currdir);

        if (finaldirectory(token, homedir, prevdir, currcopy) == 0)
        {
            printf("warp: %s: No such file or directory\n", token);
            return 0;
        }
        else
        {
            strcpy(prevdir, currdir);
            prevdir[strlen(currdir)] = '\0';
            chdir(currcopy);
            printf("%s\n",currcopy);
        }
        token = __strtok_r(NULL, " \t", &outer_saveptr);
    }
    return 1;
}