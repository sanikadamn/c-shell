#include "../headers.h"
// the functions will return 1 if the thing can happen and they will modify currcopy if it can do stuff
// they will return 0 if the thing cannot happen and in that case you print invalid directory

// this function is to "go" to the directory mentioned by the ..
int dotdot(char input[], char currcopy[])
{
    char temp[1000];
    strcpy(temp, currcopy);
    char *remove_part = strrchr(temp, '/');
    size_t length = remove_part - temp;
    if (length == 0)
        length = 1;
    temp[length] = '\0';

    if (chdir(temp) == 0)
    {
        strcpy(currcopy, temp);
        return 1;
    }
    else
        return 0;
}

int dot(char input[], char currcopy[])
{
    if (chdir(currcopy) == 0)
        return 1;
    else
        return 0;
}

int tilda(char input[], char homedir[], char currcopy[])
{
    if (chdir(homedir) == 0)
    {
        strcpy(currcopy, homedir);
        return 1;
    }
    else
        return 0;
}

int directory(char input[], char currcopy[])
{
    if (chdir(input) == 0)
    {
        strcpy(currcopy, input);
        return 1;
    }
    else
        return 0;
}

int finaldirectory(char input[], char homedir[], char prevdir[], char currcopy[])
{
    // if they give absolute path
    char tempcurr[1000];
    if(chdir(input) == 0)
    {
        // get current file
        getcwd(tempcurr, 1000);
        strcpy(currcopy, tempcurr);
        return 1;
    }
    char tempinput[1000];
    strcpy(tempinput, input);
    char* inner_saveptr = NULL;

    char *token = __strtok_r(tempinput, "/", &inner_saveptr);

    if (strcmp(token, "-") == 0 || strncmp(token, "-\n", 2) == 0)
    {
        token = __strtok_r(NULL, "/", &inner_saveptr);
        if(token != NULL)
            return 0;
        if (prevdir != NULL)
        {
            if (chdir(prevdir) == 0)
            {
                strcpy(currcopy, prevdir);
                return 1;
            }
            else
                printf("%s\n", "Error");
        }
    }

    while (token != NULL)
    {
        clear_token(token);
        if (strlen(token) == 0)
            break;
        if (strcmp(token, "~") == 0 || strncmp(token, "~\n", 2) == 0)
        {
            if (tilda(token, homedir, currcopy) == 0)
                return 0;
        }
        else if (strcmp(token, ".") == 0 || strncmp(token, ".\n", 2) == 0)
        {
            if (dot(token, currcopy) == 0)
                return 0;
        }
        else if (strcmp(token, "..") == 0 || strncmp(token, "..\n", 3) == 0)
        {
            if (dotdot(token, currcopy) == 0)
                return 0;
        }
        else
        {
            if (directory(token, currcopy) == 0)
                return 0;
        }
        token = __strtok_r(NULL, "/", &inner_saveptr);
    }

    return 1;
}
