#ifndef MY_LS_H
#define MY_LS_H

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

size_t my_strlen(const char *str);
void my_perror(const char *s);
void options(char *opt_str, int *op_a, int *op_t);
int my_strcmp(const char *s1, const char *s2);
int compare_time(const struct dirent *entry_a, const struct dirent *entry_b);
void sort_time(struct dirent **file_list, int file_count);
void sort_name(struct dirent **file_list, int file_count);
int my_ls(const char *dir, int op_a, int op_l);
int main(int argc, char **argv);

#endif
