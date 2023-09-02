#ifndef __PEEK_H__
#define __PEEK_H__
#include "unistd.h"
#include "stdio.h"
#include "dirent.h"
#include "string.h"
#include "stdlib.h"
#include "sys/stat.h"
#include "pwd.h"
#include "grp.h"
#include "time.h"
#include "sys/types.h"


int peek(int length, char *arguments[]);
void get_dir_path(char input[], char homedir[], char dir[], char prevdir[]);
int compare(const void *a, const void *b);


#endif