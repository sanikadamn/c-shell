#include "../headers.h"

void readpastevents(char path[])
{
    FILE *fp;
    fp = fopen(path, "a+");
    fclose(fp);
    fp = fopen(path, "r");
    char line[1000];
    while (fgets(line, 1000, fp) != NULL)
    {
        printf("%s", line);
    }
    fclose(fp);
    return;
}

void execute(int length, char *arguments[], char input[], char homedir[], char prevdir[], struct pr processes[], struct timeval start, struct timeval end, double timetaken, char process[], int isthethingworking)
{
    char path[1000] = {};
    strcpy(input, arguments[0]);
    input[strlen(input)] = '\0';
    // strcpy(input, arguments[0]);
    strcpy(path, arguments[3]);
    FILE *fp;
    fp = fopen(path, "a+");
    fclose(fp);
    fp = fopen(path, "r");
    char line[1000];
    int count = 0;
    while (fgets(line, 1000, fp) != NULL)
    {
        count++;
    }
    fclose(fp);
    // get the number that they want to execute
    int num = atoi(input);
    if (num > count)
    {
        printf("Invalid number\n");
        return;
    }
    fp = fopen(path, "r");
    for (int i = 0; i < count - num + 1; i++)
    {
        fgets(line, 1000, fp);
    }
    fclose(fp);
    // its in line now
    char *arguments_[] = {line, homedir, prevdir, "1", NULL};
    length = 4;
    int isthisworking = tokenize(line, homedir, prevdir, processes, start, end, timetaken, process, isthethingworking);
    if(isthisworking == 1)
    {
        char *arguments[] = {line, homedir, prevdir, "1", NULL};
        pastevents(length, arguments, input, homedir, prevdir, processes, start, end, timetaken, process, isthethingworking);
    }
        

    // int i = 1;
}

void pastevents(int length, char *arguments[], char input[], char homedir[], char prevdir[], struct pr processes[], struct timeval start, struct timeval end, double timetaken, char process[], int isthethingworking )
{
    // char input[1000] = {};
    strcpy(input, arguments[0]);
    input[strlen(input)] = '\0';
    int file = atoi(arguments[3]);

    char path[1000] = {};
    strcat(path, homedir);
    strcat(path, "/pastevents.txt");
    char *token;
    char *saveptr = NULL;
    if (file == 0)
    {
        token = __strtok_r(input, " \t", &saveptr);
        token = __strtok_r(NULL, " \t", &saveptr);
        clear_token(token);
    }
    clear_token(token);

    FILE *fp;
    // this is when the pastevents command is called
    if(file == 0 && token != NULL)
    {
        if(strlen(token) == 0)
        {
            readpastevents(path);
            return;
        }

    }

    if ((file == 0 && token == NULL))
    {
        readpastevents(path);
    }
    // case when pastevents purge is called
    else if (file == 0 && token != NULL && (strcmp(token, "purge") == 0 || strncmp(token, "purge\n", 6) == 0))
    {
        // delete pastevents.txt
        // clear the file given by path
        remove(path);
    }
    // this is for executing commands
    else if (file == 0 && token != NULL && strcmp(token, "execute") == 0)
    {
        token = __strtok_r(NULL, " ", &saveptr);
        char *arguments[] = {token, homedir, prevdir, path, NULL};
        length = 4;
        execute(length, arguments, input, homedir, prevdir, processes, start, end, timetaken, process, isthethingworking);
    }
    else if (file == 1)
    {
        // if the first token is pastevents, dont add it to the file
        // if (strcmp(input, "pastevents") == 0 || strncmp(input, "pastevents\n", 11) == 0)
        //     return;
        // make file if doesnt exist
        fp = fopen(path, "a+");
        fclose(fp);
        fp = fopen(path, "r");
        char line[1000] = {};
        int count = 0;
        char text[15][1000];
        int i = 0;
        // read the file into an array
        while (fgets(line, 1000, fp) != NULL)
        {
            count++;
            strcpy(text[i], line);
            text[i][strlen(line)] = '\0';
            i++;
        }
        fclose(fp);

        for (int j = 0; j < strlen(input); j++)
        {
            if (input[j] == '\n')
            {
                input[j] = '\0';
                break;
            }
        }

        if(count != 0)
        {
            char *ptr1 = NULL, *ptr2 = NULL;
            char temptext[1000] = {}, tempinput[1000] = {};
            strcpy(temptext, text[count - 1]);
            strcpy(tempinput, input);
            char *token1 = __strtok_r(temptext, " \t\n", &ptr1);
            char *token2 = __strtok_r(tempinput, " \t\n", &ptr2);
            clear_token(token1);
            clear_token(token2);
            int flag = 1;
            while(token1 != NULL && token2 != NULL)
            {
                clear_token(token1);
                clear_token(token2);
                // basically if the tokens are not the same
                if(strcmp(token1, token2) != 0)
                {
                    flag = 0;
                    break;
                }
                token1 = __strtok_r(NULL, " \t\n", &ptr1);
                token2 = __strtok_r(NULL, " \t\n", &ptr2);
            }
            clear_token(token1);
            clear_token(token2);
            if((token1 != NULL && strlen(token1) != 0)|| (token2 != NULL && strlen(token2) != 0))
            { 
                flag = 0;
            }
            if(flag == 1)
                return;
        }
        for (int i = 0; i < strlen(input); i++)
        {
            if (input[i] == '\n')
            {
                input[i] = '\0';
                break;
            }
        }
        if(strlen(input) == 0)
            return;

        if (count >= 15)
        {
            remove(path);
            fp = fopen(path, "a+");

            for (int j = 1; j < 15; j++)
            {
                fprintf(fp, "%s", text[j]);
            }
            fprintf(fp, "%s\n", input);
            fclose(fp);
        }
        else
        {
            fp = fopen(path, "a+");
            fprintf(fp, "%s\n", input);
            fclose(fp);
        }
    }
}