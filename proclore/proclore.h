#ifndef __PROCLORE_H__
#define __PROCLORE_H__
#include "unistd.h"
#include "termios.h"

int read_process_info(pid_t pid);
int proclore(int length, char *arguments[]);

#endif