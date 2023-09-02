#include "headers.h"
#define TRUE 1
#define FALSE 0

// need to change code to make sure the thing is split based on ;
// and then the thing is split based on &
// and then the thing is split based on |
// and then the thing is split based on >, <, <<


void remove_leading_whitespaces(char input[])
{
    int i = 0;
    while (input[i] == ' ')
    {
        i++;
    }
    int j = 0;
    while (input[i] != '\0')
    {
        input[j] = input[i];
        i++;
        j++;
    }
    input[j] = '\0';
}

// char *args[] = {token, homedir, prevdir, NULL};
struct pr processes[1000];

int main(int argc, char *argv[])
{
    // Keep accepting commands
    char homedir[1000], prevdir[1000];
    if (getcwd(homedir, sizeof(homedir)) == NULL)
    {
        perror("getcwd");
    }
    struct timeval start, end;
    double timetaken = 0;
    char process[1000] = {};

    for (int i = 0; i < 1000; i++)
    {
        processes[i].pid = -1;
    }

    strcpy(prevdir, homedir);
    while (1)
    {
        // Print appropriate prompt with username, systemname and directory before accepting input
        prompt(homedir, timetaken, process);
        checkbgprocess();
        timetaken = 0;
        char input[4096];
        fgets(input, 4096, stdin);
        remove_leading_whitespaces(input);
        char inputcopy[1000];
        strcpy(inputcopy, input);

        int isthethingworking = 1;

        // check if it starts with warp
        // remove trailing whitespaces

        char *saveptr = NULL;
        char *token = __strtok_r(input, ";", &saveptr);
        while (token != NULL)
        {
            remove_leading_whitespaces(token);

            int count = 0;
            for (int i = 0; i < strlen(token); i++)
            {
                if (token[i] == '&')
                    count++;
            }

            char *innerpts = NULL;
            char tokencopy[1000];
            strcpy(tokencopy, token);
            char *innertoken = __strtok_r(tokencopy, "&", &innerpts);
            if (count == 0)
            {
                char *arguments[] = {token, homedir, prevdir, "0", NULL};
                int length = 4;
                gettimeofday(&start, NULL);
                isthethingworking = (callfunction(length, arguments) && 1);
                strcpy(process, token);
                clear_token(process);
                gettimeofday(&end, NULL);
                // print time taken
                timetaken = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;

                token = __strtok_r(NULL, ";", &saveptr);
                continue;
            }

            char fgbg[count + 1][1000];

            int counter = 0;
            while (innertoken != NULL && counter < count + 1)
            {
                remove_leading_whitespaces(innertoken);
                strcpy(fgbg[counter], innertoken);
                innertoken = __strtok_r(NULL, "&", &innerpts);
                counter++;
            }

            // fork the process
            // fork the process count number of times

            for (int i = 0; i < count; i++)
            {
                pid_t pid = fork();
                char processname[1000] = {};
                // get the first token of fgbg[i] and put it in processname
                char *saveptr2 = NULL;
                char *token2 = __strtok_r(fgbg[i], " \t\n", &saveptr2);
                strcpy(processname, token2);
                clear_token(processname);

                if (pid == -1)
                {
                    perror("fork");
                    exit(EXIT_FAILURE);
                }
                else if (pid == 0)
                {
                    setpgid(0, 0);
                    // char *arguments[] = {fgbg[i], homedir, prevdir, "0", NULL};
                    // int length = 4;
                    // break fgbg[i] into tokens based on " /t"
                    char *tokens[100];
                    for (int i = 0; i < 100; i++)
                    {
                        tokens[i] = (char *)malloc(100 * sizeof(char));
                    }

                    int counter = 0;
                    while (token2 != NULL)
                    {
                        strcpy(tokens[counter], token2);
                        token2 = strtok_r(NULL, " \t\n", &saveptr2);
                        counter++;
                    }
                    tokens[counter] = NULL;
                    execvp(tokens[0], tokens);
                }
                else
                {
                    // add the process to the array
                    // iterate through array to find -1 pid
                    for (int i = 0; i < 1000; i++)
                    {
                        if (processes[i].pid == -1)
                        {
                            processes[i].pid = pid;
                            strcpy(processes[i].name, processname);
                            processes[i].index = i + 1;
                            printf("[%d] %s with pid %d started\n", processes[i].index, processes[i].name, processes[i].pid);
                            break;
                        }
                    }
                }
            }

            char *arguments[] = {fgbg[count], homedir, prevdir, "0", NULL};
            int length = 4;
            gettimeofday(&start, NULL);
            isthethingworking = (callfunction(length, arguments) && 1);
            strcpy(process, token);
            clear_token(process);
            gettimeofday(&end, NULL);
            // print time taken
            timetaken = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;

            token = __strtok_r(NULL, ";", &saveptr);
        }
        // if pastevents isnt called
        if (isthethingworking == 1)
        {
            char *arguments[] = {inputcopy, homedir, prevdir, "1", NULL};
            int length = 4;
            pastevents(length, arguments);
        }
    }
}
