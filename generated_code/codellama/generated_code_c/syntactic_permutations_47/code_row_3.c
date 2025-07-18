#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include "mime_types.h"

#define DIRLEN 256
#define MAX_FILENAME_LEN 255

struct dirent *dp;

int main(void) {
    char *dirname = "/var/www/images";
    char file_name[MAX_FILENAME_LEN + 1];
    strcpy(file_name, dirname);
    strcat(file_name, "/");
    int c;

    DIR *dir = opendir(dirname);
    if (dir) {
        while ((dp = readdir(dir)) != NULL) {
            char *mime_type;
            char full_file_name[DIRLEN];
            struct stat file_info;

            strcpy(full_file_name, dirname);
            strcat(full_file_name, "/");
            strcat(full_file_name, dp->d_name);

            if (stat(full_file_name, &file_info) == 0) {
                mime_type = get_mime_type(dp->d_name);
                printf("Content-Type: %s\n\n", mime_type);
                FILE *fp;
                char *mode = "r";
                fp = fopen(full_file_name, mode);

                if (fp == NULL) {
                    printf("Error opening file");
                    return 1;
                }
                c = fgetc(fp);
                while (c != EOF) {
                    putchar(c);
                    c = fgetc(fp);
                }

                if (fclose(fp) != 0) {
                    printf("Error closing file");
                    return 1;
                }
            }
        }
        closedir(dir);
    } else {
        perror("Couldn't open the directory");
    }

    return 0;
}