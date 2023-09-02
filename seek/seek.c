#include "../headers.h"
#define TRUE 1
#define FALSE 0

int count = 0;
char f_flag[1000] = {};
int is_file = FALSE;

void searchforfiles(const char *dir, const char *file, const char *tempdir, int d, int e, int f, int noflag)
{
    DIR *open_directory = opendir(dir);
    if (open_directory == NULL)
    {
        perror("Error opening directory");
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(open_directory)) != NULL)
    {
        char tempfile[1000] = {}, tempentry[1000];
        strcpy(tempfile, file);
        strcpy(tempentry, entry->d_name);
        strcat(tempfile, ".");
        strcat(tempentry, ".");

        if (entry->d_type == 4 && strcmp(entry->d_name, file) == 0)
        {
            // remove the part of
            if (d == TRUE || e == TRUE || noflag == TRUE)
            {
                printf("\033[1;34m.%s/%s\033[0m\n", &dir[strlen(tempdir)], entry->d_name);
                count++;
            }
            is_file = FALSE;

            strcpy(f_flag, dir);
            strcat(f_flag, "/");
            strcat(f_flag, entry->d_name);
            int size = strlen(dir) + strlen(entry->d_name) + 1;
            f_flag[size] = '\0';
        }

        if (entry->d_type == 4 && strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
        {
            // Construct the path of the subdirectory
            char subPath[1000];
            snprintf(subPath, sizeof(subPath), "%s/%s", dir, entry->d_name);
            searchforfiles(subPath, file, tempdir, d, e, f, noflag);
        }
        else if (entry->d_type == 8 && (strncmp(entry->d_name, tempfile, (strlen(file) + 1)) == 0 || strncmp(tempentry, tempfile, strlen(tempfile)) == 0))
        {
            // Found the target file, print the relative path
            // remove the tempdir length from dir
            if (f == TRUE || e == TRUE || noflag == TRUE)
            {
                printf("\033[1;32m.%s/%s\033[0m\n", &dir[strlen(tempdir)], entry->d_name);
                strcpy(f_flag, dir);
                strcat(f_flag, "/");
                strcat(f_flag, entry->d_name);
                int size = strlen(dir) + strlen(entry->d_name) + 1;
                f_flag[size] = '\0';
                is_file = TRUE;
                count++;
            }
        }
    }

    closedir(open_directory);
}

int seek(int length, char *arguments[])
{
    count = 0;
    char input[1000] = {}, homedir[1000] = {}, prevdir[1000] = {};
    strcpy(input, arguments[0]);
    strcpy(homedir, arguments[1]);
    strcpy(prevdir, arguments[2]);

    int d = FALSE, e = FALSE, f = FALSE, directory = FALSE, file_ = FALSE, noflag = FALSE;
    // get initial directory
    char dir[1000], tempdir[1000];
    char file[1000];
    if (getcwd(dir, sizeof(dir)) == NULL)
    {
        perror("getcwd");
        return 0;
    }
    strcpy(tempdir, dir);
    char *saveptr = NULL;
    char *token = __strtok_r(input, " \t", &saveptr);
    token = __strtok_r(NULL, " \t", &saveptr);
    clear_token(token);
    while (token != NULL && strlen(token) != 0)
    {
        clear_token(token);
        if (strcmp(token, "-d") == 0 || strcmp(token, "-d\n") == 0)
        {
            d = TRUE;
        }
        else if (strcmp(token, "-e") == 0 || strcmp(token, "-e\n") == 0)
        {
            e = TRUE;
        }
        else if (strcmp(token, "-f") == 0 || strcmp(token, "-f\n") == 0)
        {
            f = TRUE;
        }
        else if (strncmp(token, "-", 1) == 0)
        {
            printf("Invalid Flag\n");
            return 0;
        }
        else if (file_ == FALSE)
        {
            file_ = TRUE;
            strcpy(file, token);
        }
        else
        {
            finaldirectory(token, homedir, prevdir, dir);
            chdir(tempdir);
            directory = TRUE;
        }
        // flags(flag, token, homedir, prevdir, dir);
        token = __strtok_r(NULL, " \t", &saveptr);
        clear_token(token);
    }
    if (file_ == FALSE)
    {
        printf("No file specified!\n");
        return 0;
    }
    if (d == TRUE && f == TRUE)
    {
        printf("Invalid flags!\n");
        return 0;
    }
    if(d == FALSE && e == FALSE && f == FALSE)
    {
        noflag = TRUE;
    }
    searchforfiles(dir, file, tempdir, d, e, f, noflag);

    if (count == 0)
    {
        printf("No Match Found\n");
        return 0;
    }

    if (e == TRUE && count == 1 && is_file == TRUE)
    {
        // read f_flag file and print its contents
        FILE *ptr;
        ptr = fopen(f_flag, "r");

        if (NULL == ptr)
        {
            printf("Missing permissions for task! \n");
        }

        char ch;
        while (ch != EOF)
        {
            ch = fgetc(ptr);
            if (ch == EOF)
            {
                break;
            }
            printf("%c", ch);
        }
        if (ch != '\n')
            printf("\n");
    }
    else if (e == TRUE && count == 1 && is_file == FALSE)
    {
        chdir(f_flag);
    }

    return 1;
    // printf("%s\n", f_flag);

    // printf("%s\n", dir);
}