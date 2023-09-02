#include "../headers.h"
#define TRUE 1
#define FALSE 0

void get_dir_path(char input[], char homedir[], char dir[], char prevdir[])
{
    char *currdir = getcwd(NULL, 0);
    
    if(finaldirectory(input, homedir, prevdir, dir) == 0)
    {
        printf("warp: %s: No such file or directory\n", input);
        return;
    }
    else 
    {
        chdir(currdir);
    }
}

int compare(const void *a, const void *b)
{
    // copy into temp array without the leading . to make sure sorting is correct
    char temp1[1000], temp2[1000];
    if ((*(struct dirent **)a)->d_name[0] == '.')
        strcpy(temp1, (*(struct dirent **)a)->d_name + 1);
    else
        strcpy(temp1, (*(struct dirent **)a)->d_name);
    if ((*(struct dirent **)b)->d_name[0] == '.')
        strcpy(temp2, (*(struct dirent **)b)->d_name + 1);
    else
        strcpy(temp2, (*(struct dirent **)b)->d_name);
    return strcasecmp(temp1, temp2);
}

void print_permissions(mode_t mode)
{
    putchar((S_ISDIR(mode)) ? 'd' : '-');
    putchar((mode & S_IRUSR) ? 'r' : '-');
    putchar((mode & S_IWUSR) ? 'w' : '-');
    putchar((mode & S_IXUSR) ? 'x' : '-');
    putchar((mode & S_IRGRP) ? 'r' : '-');
    putchar((mode & S_IWGRP) ? 'w' : '-');
    putchar((mode & S_IXGRP) ? 'x' : '-');
    putchar((mode & S_IROTH) ? 'r' : '-');
    putchar((mode & S_IWOTH) ? 'w' : '-');
    putchar((mode & S_IXOTH) ? 'x' : '-');
}

int peek(int length, char *arguments[])
{
    char input[1000] = {}, homedir[1000] = {}, prevdir[1000] = {};
    strcpy(input, arguments[0]);
    strcpy(homedir, arguments[1]);
    strcpy(prevdir, arguments[2]);

    char *saveptr = NULL;
    int a = FALSE, l = FALSE, first_flag = FALSE, dir_flag = FALSE;
    char *token = __strtok_r(input, " \t", &saveptr);
    token = __strtok_r(NULL, " \t", &saveptr);
    clear_token(token);

    char dir[1000];

    // first flag which can be -a, -l, -al, -la
    if (token != NULL && token[0] == '-')
    {
        if (strcmp(token, "-a") == 0 || strcmp(token, "-a\n") == 0)
            a = TRUE;
        else if (strcmp(token, "-l") == 0 || strcmp(token, "-l\n") == 0)
            l = TRUE;
        else if (strcmp(token, "-al") == 0 || strcmp(token, "-al\n") == 0 || strcmp(token, "-la") == 0 || strcmp(token, "-la\n") == 0)
        {
            a = TRUE;
            l = TRUE;
        }
        else if (strcmp(token, "-") == 0 || strncmp(token, "-\n", 2) || strncmp(token, "-\t", 2) == 0  || strncmp(token, "- ", 2) == 0)
        {
            get_dir_path("-", homedir, dir, prevdir);
            dir_flag = TRUE;
        }
        else 
        {
            printf("Invalid Flags\n");
            return 0;
        }
        token = __strtok_r(NULL, " \t", &saveptr);
        clear_token(token);
        first_flag = TRUE;
    }
    // no flag + directory name mentioned
    else if (token != NULL && dir_flag == FALSE)
    {
        if (strlen(token) == 0)
        {
            get_dir_path(".", homedir, dir, prevdir);
        }
        else
            get_dir_path(token, homedir, dir, prevdir);

        dir_flag = TRUE;
    }
    // no flag + no directory name mentioned
    else if (token == NULL)
    {
        get_dir_path(".", homedir, dir, prevdir);
    }

    // in this case it is a flag yay
    if (first_flag == TRUE && token != NULL && token[0] == '-')
    {
        if (strcmp(token, "-a") == 0 || strcmp(token, "-a\n") == 0)
            a = TRUE;
        else if (strcmp(token, "-l") == 0 || strcmp(token, "-l\n") == 0)
            l = TRUE;
        else
        {
            printf("Invalid Flags\n");
            return 0;
        }
        token = __strtok_r(NULL, " \t", &saveptr);
        if (token != NULL)
            clear_token(token);
    }
    // the second thing is a directory name! yay :D
    else if (first_flag == TRUE && token != NULL)
    {
        if (strlen(token) == 0)
        {
            get_dir_path(".", homedir, dir, prevdir);
        }
        else
        {
            get_dir_path(token, homedir, dir, prevdir);
        }
        dir_flag = TRUE;
    }
    // the second thing is nothing :(
    else if (first_flag == TRUE && token == NULL)
    {
        get_dir_path(".", homedir, dir, prevdir);
        dir_flag = TRUE;
    }

    // the first two things were tokens xD
    if (first_flag == TRUE && dir_flag == FALSE && token == NULL)
    {
        get_dir_path(".", homedir, dir, prevdir);
    }
    else if (first_flag == TRUE && dir_flag == FALSE && token != NULL)
    {
        if (strlen(token) == 0)
        {
            get_dir_path(".", homedir, dir, prevdir);
        }
        else
            get_dir_path(token, homedir, dir, prevdir);
    }

    DIR *directory;
    struct dirent *entry;

    // Open the directory
    directory = opendir(dir);
    if (directory == NULL)
    {
        perror("opendir");
        return 0;
    }

    int num_files = 0;
    while ((entry = readdir(directory)) != NULL)
        num_files++;

    // Allocate memory for file_names array
    struct dirent **file_names = (struct dirent **)malloc(num_files * sizeof(struct dirent *));
    if (file_names == NULL)
    {
        perror("malloc");
        closedir(directory);
        return 0;
    }
    rewinddir(directory);

    int i = 0;
    while ((entry = readdir(directory)) != NULL)
    {
        file_names[i] = entry;
        i++;
    }

    // sort the array
    qsort(file_names, num_files, sizeof(struct dirent *), compare);
    // print the array
    for (int j = 0; j < i; j++)
    {
        // Get file stats
        struct stat file_stat;
        char path[1000];
        strcpy(path, dir);
        strcat(path, "/");
        strcat(path, file_names[j]->d_name);

        // pretty print based on flags provided
        if (stat(path, &file_stat) == 0)
        {
            if (a == FALSE && file_names[j]->d_name[0] == '.')
                continue;
            if (l == TRUE)
            {
                print_permissions(file_stat.st_mode);
                printf(" %ld", file_stat.st_nlink);

                struct passwd *user_info = getpwuid(file_stat.st_uid);
                struct group *group_info = getgrgid(file_stat.st_gid);

                if (user_info != NULL)
                {
                    printf(" %s", user_info->pw_name);
                }

                if (group_info != NULL)
                {
                    printf(" %s\t", group_info->gr_name);
                }

                printf("%ld\t", file_stat.st_size);

                char time_str[20];
                strftime(time_str, sizeof(time_str), "%b %d %H:%M", localtime(&file_stat.st_mtime));
                printf(" %s\t", time_str);
            }
            // the colors
            if (file_names[j]->d_type == 4)
                printf("\033[1;34m%s\033[0m\n", file_names[j]->d_name);
            else if (file_stat.st_mode & S_IXUSR)
                printf("\033[1;32m%s\033[0m\n", file_names[j]->d_name);
            else
                printf("\033[1;37m%s\033[0m\n", file_names[j]->d_name);
        }
        else
        {
            perror("stat");
            return 0;
        }
    }

    // Close the directory
    closedir(directory);
    return 1;
}