#include "my_ls.h"

size_t my_strlen(const char *str) {
    size_t length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

void my_perror(const char *s) {
    if (s != NULL && *s != '\0') {
        write(STDERR_FILENO, s, my_strlen(s));
    }
}

void options(char *opt_str, int *op_a, int *op_t) {
    char *p = opt_str + 1;
    while (*p) {
        if (*p == 'a') *op_a = 1;
        else if (*p == 't') *op_t = 1;
        else {
            my_perror("Syntax error");
        }
        p++;
    }
}

int my_strcmp(const char *s1, const char *s2) {
    while (*s1 && *s1 == *s2) {
        s1++;
        s2++;
    }
    return (unsigned char)(*s1) - (unsigned char)(*s2);
}

int compare_time(const struct dirent *entry_a, const struct dirent *entry_b) {
    struct stat stat_a, stat_b;

    if (stat(entry_a->d_name, &stat_a) == -1 || stat(entry_b->d_name, &stat_b) == -1) {
        return 0;
    } 

    if (stat_a.st_mtim.tv_sec == stat_b.st_mtim.tv_sec) {
        return stat_b.st_mtim.tv_nsec - stat_a.st_mtim.tv_nsec;
    }
    return stat_b.st_mtim.tv_sec - stat_a.st_mtim.tv_sec;
}

void sort_time(struct dirent **file_list, int file_count) {
    for (int i = 1; i < file_count; i++) {
        struct dirent *key = file_list[i];
        int j = i - 1;
        while (j >= 0 && compare_time(file_list[j], key) > 0) {
            file_list[j + 1] = file_list[j];
            j--;
        }
        file_list[j + 1] = key;
    }
}

void sort_name(struct dirent **file_list, int file_count) {
    for (int i = 1; i < file_count; i++) {
        struct dirent *key = file_list[i];
        int j = i - 1;
       
        while (j >= 0 && my_strcmp(file_list[j]->d_name, key->d_name) > 0) {
            file_list[j + 1] = file_list[j];
            j--;
        }
        file_list[j + 1] = key;
    }
}

int my_ls(const char *dir, int op_a, int op_t) {
    struct dirent *d;
    DIR *ptr = opendir(dir);
    if (!ptr) {
        struct stat statbuf;
        if (stat(dir, &statbuf) == -1) {
            my_perror(dir);
            my_perror("No such file or directory\n");
        } else {
            my_perror(dir);
            my_perror("Not a directory\n");
        }
        return EXIT_FAILURE;
    }

    int max = 10;
    int file_count = 0;
    struct dirent **file_list = malloc(max * sizeof(struct dirent *));
    if (!file_list) {
        my_perror("Memory allocation error\n");
        closedir(ptr);
        return EXIT_FAILURE;
    }

    while ((d = readdir(ptr)) != NULL) {
        if (!op_a && d->d_name[0] == '.') {
            continue; 
        }

        if (file_count == max) {
            max *= 2;
            struct dirent **new_list = malloc(max * sizeof(struct dirent *));
            if (!new_list) {
                my_perror("Memory allocation error\n");
                free(file_list);
                closedir(ptr);
                return EXIT_FAILURE;
            }

            for (int i = 0; i < file_count; i++) {
                new_list[i] = file_list[i];
            }
            free(file_list);
            file_list = new_list;
        }
        file_list[file_count++] = d;
    }

    if (op_t) {
        sort_time(file_list, file_count);
    } else {
        sort_name(file_list, file_count);
    }

    for (int i = 0; i < file_count; i++) {
        printf("%s\n", file_list[i]->d_name);
    }

    free(file_list);
    closedir(ptr);
    return 0;
}

int main(int argc, char **argv) {
    int op_a = 0, op_t = 0;

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            options(argv[i], &op_a, &op_t);
        }
    }

    if (argc == 1 || (argc == 2 && argv[1][0] == '-')) {
        my_ls(".", op_a, op_t); 
    } else {

        for (int i = 1; i < argc; i++) {
            if (argv[i][0] != '-') {
                if (my_ls(argv[i], op_a, op_t) == EXIT_FAILURE) {
                    continue;  
                }
            }
        }
    }
    return 0;
}
