#include <stdio.h>
#include <stdlib.h>
#include <string.h>  
#include<sys/types.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>

void file_upload() {
    // create a file for writing
    FILE *fp;
    fp = fopen("file", "w");

    // check if the file opened successfully
    if (fp == NULL) {
        perror("Error opening file\n");
        exit(1);
    }

    // read the file and print its contents
    char ch;
    while ((ch = fgetc(fp)) != EOF)
        printf("%c", ch);

    // close the file
    if (fclose(fp) == -1)
        perror("Error closing file\n");
}