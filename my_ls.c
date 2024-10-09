#include "my_ls.h"

int my_strcmp(const char *a, const char *b)
{
    while (*a && *b && *a == *b) {
        a++;
        b++;
    }
    return *a - *b;
}


void sort_name(struct dirent *entries[], int count) {
    for (int i = 1; i < count; i++) {
        struct dirent * key = entries[i];
        int j = i - 1;

        while (j >= 0 && my_strcmp(entries[j]->d_name, key ->d_name) > 0) {
            entries[j + 1] = entries[j];
            j--;
        }
        entries[j + 1] = key;
    }
}

int list_dir(const char *dir_name, int op_a, int op_t){
   DIR *dir;
   struct dirent *entry; 
   struct dirent *entries[MAX_ENTRIES];  
   int count = 0;

    dir = opendir(dir_name);
    if (dir == NULL) {
        printf("ls: cannot access '%s': No such file or directory", dir_name);
        return 1;
    }

    while ((entry = readdir(dir)) != NULL) {
        if(!op_a && entry->d_name[0] == '.'){
            continue;
        }
        if (count < MAX_ENTRIES) {
            entries[count++] = entry;  
        }
    }
    closedir(dir);

    if(op_t){
        printf("option T\n");
    } else {
        sort_name(entries, count);
    }
    
    for (int i = 0; i < count; i++) {
        printf("%s\n", entries[i]->d_name);
    }

    return 0;
}


int main(int argc, char **argv) {
    int op_a = 0;
    int op_t = 0;
    char *directories[argc]; 
    int dir_count = 0; 
  
       for (int i = 1; i < argc; i++) {
           if (argv[i][0] == '-') { 
               for (int j = 1; argv[i][j] != '\0'; j++) { 
                   if (argv[i][j] == 'a') {
                       op_a = 1;  
                    } else if (argv[i][j] == 't') {
                       op_t = 1;  
                    } else {
                       printf("Wrong flag");
                       return 1;
                    }
                }
            } else { 
               directories[dir_count++] = argv[i];  
            }
        }
    
    if (dir_count == 0) {
        directories[dir_count++] = ".";  
    }
    for (int i = 0; i < dir_count; i++) {
        list_dir(directories[i], op_a, op_t); 
    }
    return 0;
}
