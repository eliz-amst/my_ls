#include "my_ls.h"
// custom strlen
size_t my_strlen(const char *str) {
    size_t length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}
// Custom string comparison function (replaces strcmp)
int my_strcmp(const char *a, const char *b) {
    while (*a && *b && *a == *b) {
        a++;
        b++;
    }
    return *a - *b;
}
void swap(char **a, char **b) {
    char *temp = *a;
    *a = *b;
    *b = temp;
}
// Custom string copy function
void my_strcpy(char *dest, const char *src) {
    while (*src) {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';  // Null-terminate the string
}
// Custom string concatenation function
void my_strcat(char *dest, const char *src) {
    // Move `dest` pointer to the end of the existing string
    while (*dest) {
        dest++;
    }
    // Copy the `src` string to `dest`
    while (*src) {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';  // Null-terminate the string
}
// Custom function to copy dirent struct
void copy_dirent(struct dirent *dest, const struct dirent *src) {
    dest->d_ino = src->d_ino;
    dest->d_off = src->d_off;
    dest->d_reclen = src->d_reclen;
    dest->d_type = src->d_type;
    int i = 0;
    while (src->d_name[i] != '\0' && i < NAME_MAX) {
        dest->d_name[i] = src->d_name[i];
        i++;
    }
    dest->d_name[i] = '\0';  // Null-terminate the string
}
// Sort files by name
void sort_name(struct dirent *entries[], int count) {
    for (int i = 1; i < count; i++) {
        struct dirent *key = entries[i];
        int j = i - 1;
        while (j >= 0 && my_strcmp(entries[j]->d_name, key->d_name) > 0) {
            entries[j + 1] = entries[j];
            j--;
        }
        entries[j + 1] = key;
    }
}
// Sort files by modification time
void sort_time(struct dirent *entries[], struct timespec *times, int count) {
    for (int i = 1; i < count; i++) {
        struct dirent *key = entries[i];
        struct timespec key_time = times[i];
        int j = i - 1;
        // Compare by tv_sec first, then by tv_nsec for finer granularity
        while (j >= 0 && (times[j].tv_sec < key_time.tv_sec ||
                (times[j].tv_sec == key_time.tv_sec && times[j].tv_nsec < key_time.tv_nsec))) {
            entries[j + 1] = entries[j];
            times[j + 1] = times[j];
            j--;
        }
        entries[j + 1] = key;
        times[j + 1] = key_time;
    }
}
int list_dir(const char *dir_name, int op_a, int op_t) {
    DIR *dir;
    struct dirent *entry;
    struct dirent *entries[MAX_ENTRIES];
    struct timespec times[MAX_ENTRIES]; // Store modification times
    struct stat file_stat;
    int count = 0;
    dir = opendir(dir_name);
    if (dir == NULL) {
        printf("ls: cannot access '%s': No such file or directory\n", dir_name);
        return 1;
    }
    while ((entry = readdir(dir)) != NULL) {
        if (!op_a && entry->d_name[0] == '.') {
            continue;  // Skip hidden files unless -a is specified
        }
        if (count < MAX_ENTRIES) {
            // Allocate memory for each entry and copy the dirent data
            entries[count] = malloc(sizeof(struct dirent));
            if (entries[count] == NULL) {
                printf("malloc failed\n");
                closedir(dir);
                return 1;
            }
            copy_dirent(entries[count], entry);
            // Get the file's stat info to retrieve modification time
            int filepath_len = my_strlen(dir_name) + my_strlen(entry->d_name) + 2;
            char *filepath = malloc(filepath_len);  // Allocate space for dir_name + "/" + entry->d_name + '\0'
            if (!filepath) {
                printf("malloc failed\n");
                closedir(dir);
                return 1;
            }
            my_strcpy(filepath, dir_name);
            my_strcat(filepath, "/");
            my_strcat(filepath, entry->d_name);
            if (stat(filepath, &file_stat) == 0) {
                times[count] = file_stat.st_mtim; // Store modification time
            } else {
                // Handle stat failure (e.g., file deleted between readdir and stat)
                times[count].tv_sec = 0;
                times[count].tv_nsec = 0;
            }
            free(filepath);  // Free the allocated memory for filepath
            count++;
        }
    }
    closedir(dir);
    // Sort by time if -t is provided, otherwise by name
    if (op_t) {
        sort_time(entries, times, count);
    } else {
        sort_name(entries, count);
    }
    // Print the sorted list of files
    for (int i = 0; i < count; i++) {
        printf("%s\n", entries[i]->d_name);
        free(entries[i]);  // Free allocated memory for each entry
    }
    return 0;
}
int main(int argc, char **argv) {
    int op_a = 0;
    int op_t = 0;
    char *directories[argc];
    int dir_count = 0;
    // Parse arguments for options and directories
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            for (int j = 1; argv[i][j] != '\0'; j++) {
                if (argv[i][j] == 'a') {
                    op_a = 1;  // Show hidden files
                } else if (argv[i][j] == 't') {
                    op_t = 1;  // Sort by time
                } else {
                    printf("Wrong flag\n");
                    return 1;
                }
            }
        } else {
            directories[dir_count++] = argv[i];
        }
    }
    if (dir_count == 0) {
        directories[dir_count++] = ".";  // Default to current directory
    }
    // Sort directories if there are multiple
    if (dir_count > 1) {
        for (int i = 0; i < dir_count - 1; i++) {
            for (int j = 0; j < dir_count - i - 1; j++) {
                if (my_strcmp(directories[j], directories[j + 1]) > 0) {
                    swap(&directories[j], &directories[j + 1]);
                }
            }
        }
    }
    // List each directory specified
    for (int i = 0; i < dir_count; i++) {
        if (i != 0) {
            printf("\n");
        }
        if (dir_count > 1) {
            printf("%s:\n", directories[i]);
        }
        list_dir(directories[i], op_a, op_t);
    }
    return 0;
}
