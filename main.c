#include "headers.h"
#define TRUE 1
#define FALSE 0

// need to change code to make sure the thing is split based on ;
// and then the thing is split based on &
// and then the thing is split based on |
// and then the thing is split based on >, <, <<

// void remove_leading_whitespaces(char input[])
// {
//     int i = 0;
//     while (input[i] == ' ')
//     {
//         i++;
//     }
//     int j = 0;
//     while (input[i] != '\0')
//     {
//         input[j] = input[i];
//         i++;
//         j++;
//     }
//     input[j] = '\0';
// }

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

        isthethingworking = (tokenize(input, homedir, prevdir, processes, start, end, timetaken, process, isthethingworking) && 1);
        if (isthethingworking == 1)
        {
            char *arguments[] = {inputcopy, homedir, prevdir, "1", NULL};
            int length = 4;
            pastevents(length, arguments, input, homedir, prevdir, processes, start, end, timetaken, process, isthethingworking);
        }

    }
}
