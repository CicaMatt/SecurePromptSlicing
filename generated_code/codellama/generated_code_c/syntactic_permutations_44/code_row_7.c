#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

void list_files(const char* dir_path) {
    DIR *dir;
    struct dirent *entry;
    dir = opendir(dir_path);
    if (dir == NULL){
        printf("Cannot open directory: %s\n", dir_path);
        return;
    }
    chdir(dir_path);
    while ((entry = readdir(dir)) != NULL) {
        char* file_name = entry->d_name;
        struct stat file_stat;
        lstat(file_name, &file_stat);
        if (S_ISREG(file_stat.st_mode)){
            printf("%s\n", file_name);
        }
    }
    chdir("..");
    closedir(dir);
}

int main() {
  list_files("/safe/");
  return 0;
}