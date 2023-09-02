#include "../headers.h"

void checkbgprocess()
{
    int status;
    pid_t pid;
    for (int i = 0; i < 1000; i++)
    {
        if (processes[i].pid != -1)
        {
            pid = waitpid(processes[i].pid, &status, WNOHANG);
            if (pid == 0)
            {
                // process is still running
                continue;
            }
            else
            {
                // process has ended
                printf("\n[%d] %s with pid %d exited normally\n", processes[i].index, processes[i].name, processes[i].pid);
                processes[i].pid = -1;
            }
        }
    }

    // shift the array if process[i].pid = -1
    for (int i = 0; i < 1000; i++)
    {
        if (processes[i].pid == -1)
        {
            for (int j = i + 1; j < 1000; j++)
            {
                if (processes[j].pid != -1)
                {
                    processes[i].pid = processes[j].pid;
                    strcpy(processes[i].name, processes[j].name);
                    processes[j].pid = -1;
                    break;
                }
            }
        }
    }

    return;
}