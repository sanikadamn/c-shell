#include "../headers.h"

int read_process_info(pid_t pid) {
    char proc_path[1000], procmpath[1000], virtualmemory[1000];
    snprintf(proc_path, sizeof(proc_path), "/proc/%d/%s", pid, "status");
    snprintf(procmpath, sizeof(procmpath), "/proc/%d/%s", pid, "statm");
    char *saveptr = NULL;
    FILE *fp = fopen(proc_path, "r");
    if (fp == NULL) {
        perror("Failed to open file");
        return 0;
    }

    char line[1024];
    char processtatus[2];
    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, "State:")) {
            processtatus[0] =  line[7];
            break;
        }
    }
    fclose(fp);

    fp = fopen(procmpath, "r");
    if (fp == NULL) {
        perror("Failed to open file");
        return 0;
    }
    while (fgets(line, sizeof(line), fp)) {
        strcpy(virtualmemory, line);
    }
    fclose(fp);
    pid_t pgid = getpgid(pid);
    char *vm = __strtok_r(virtualmemory, " \t", &saveptr);

    char exe_path[1024];
    snprintf(exe_path, sizeof(exe_path), "/proc/%d/exe", pid);

    char resolved_path[1024];
    ssize_t len = readlink(exe_path, resolved_path, sizeof(resolved_path) - 1);

    if (len != -1) {
        resolved_path[len] = '\0';
    } else {
        return 0;
    }

    // checking if the process is the same as the terminal process
    struct termios terminos;
    tcgetattr(STDIN_FILENO, &terminos);
    tcsetpgrp(STDIN_FILENO, pgid);
    pid_t tgrp = tcgetpgrp(STDIN_FILENO);
    tcsetattr(STDIN_FILENO, TCSANOW, &terminos);

    if (tgrp == pgid)
        processtatus[1] = '+';
    
    printf("pid : %d\n", pid);
    printf("Process Status : %s\n", processtatus);
    printf("Process Group ID : %d\n", pgid);
    printf("Virtual Memory : %s\n", vm);

    printf("Executable Path : %s\n", resolved_path);
    return 1;

}

int proclore(int length, char *arguments[])
{
    char currdir[1000];
    getcwd(currdir, sizeof(currdir));
    // tokenize token with strtok
    char *saveptr = NULL;
    char argumentscopy[1000];
    strcpy(argumentscopy, arguments[0]);
    char *token = __strtok_r(arguments[0], " \t", &saveptr);
    token = __strtok_r(NULL, " \t", &saveptr);
    clear_token(token);
    pid_t pid;
    if(token == NULL)
    {
        pid = getpid();
    }
    else if (strlen(token) == 0)
    {
        pid = getpid();
    }
    else
    {
        pid = atoi(token);
    }
    if (read_process_info(pid) == 1);
        return 1;
    return 0;
}
