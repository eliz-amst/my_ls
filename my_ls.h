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

int my_strcmp(const char *a, const char *b);
void copy_dirent(struct dirent *dest, const struct dirent *src);
void sort_name(struct dirent *entries[], int count);
void sort_time(struct dirent *entries[], struct timespec *times, int count);
int list_dir(const char *dir_name, int op_a, int op_t);
int main(int argc, char **argv);

#endif
