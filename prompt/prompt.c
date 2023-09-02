#include "../headers.h"

void prompt(char homedir[], double timetaken, char process[])
{
    // Do not hardcode the prmopt
    // get username and system name from linx
    char username[1000];
    char hostname[1000];

    if (getlogin_r(username, sizeof(username)) != 0)
    {
        perror("getlogin");
    }

    if (gethostname(hostname, sizeof(hostname)) != 0)
    {
        perror("gethostname");
    }
    // get working directory
    char cwd[1000];
    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        perror("getcwd");
    }
    // remove part of cwd that matches homedir
    if (strlen(cwd) == strlen(homedir))
    {
        cwd[0] = '~';
        cwd[1] = '\0';
    }
    else if (strlen(cwd) > strlen(homedir))
    {
        int i = strlen(homedir);
        char temp[1000];
        temp[0] = '~';
        int j = 1;
        while (cwd[i] != '\0')
        {
            temp[j] = cwd[i];
            i++;
            j++;
        }
        temp[j] = '\0';
        strcpy(cwd, temp);
    }
    if((int)timetaken > 2)
    {
        printf("<\033[1;32m%s\033[0m@\033[1;35m%s\033[0m:\033[1;34m%s\033[0m %s : %ds> ", username, hostname, cwd, process, (int)timetaken);
        // printf("nooo:D %lf, %s\n", timetaken, process);
    }
    else
        printf("<\033[1;32m%s\033[0m@\033[1;35m%s\033[0m:\033[1;34m%s\033[0m> ", username, hostname, cwd);
}

// \033[1;34m%s\033[0m for blue
