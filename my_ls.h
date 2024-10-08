#ifndef MY_LS_H
#define MY_LS_H

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>

#define EXIT_FAILURE 1
#define MAX_ENTRIES 1000
int list_dir(const char *dir, int op_a, int op_t);
int main(int argc, char **argv);

#endif
