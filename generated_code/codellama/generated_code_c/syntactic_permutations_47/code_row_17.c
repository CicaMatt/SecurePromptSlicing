#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* get_path(int id) {
    char *buffer;
    buffer = (char*) malloc(100);
    strcpy(buffer, "images/");
    sprintf(strcat(buffer, "%d"), id);
    return buffer;
}

void file_exist(char* path) {
    FILE *fp;
    fp = fopen(path, "r");
    if (fp == NULL) {
        printf("File %s does not exist\n", path);
        exit(1);
    } else {
        printf("File %s exists\n", path);
    }
}