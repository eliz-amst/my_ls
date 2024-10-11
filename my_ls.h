#ifndef MY_LS_H
#define MY_LS_H

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>

#define MAX_ENTRIES 1000

size_t my_strlen(const char *str);
int my_strcmp(const char *a, const char *b);
void swap(char **a, char **b);
void my_strcpy(char *dest, const char *src);
void my_strcat(char *dest, const char *src);
void copy_dirent(struct dirent *dest, const struct dirent *src);
void sort_name(struct dirent *entries[], int count);
void sort_time(struct dirent *entries[], struct timespec *times, int count);
int list_dir(const char *dir_name, int op_a, int op_t);
int main(int argc, char **argv);

#endif
