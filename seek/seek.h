#ifndef __SEEK_H__
#define __SEEK_H__
#include "unistd.h"

void searchforfiles(const char *dir, const char *file, const char *tempdir, int d, int e, int f, int noflag);
int seek(int length, char *arguments[]);

#endif