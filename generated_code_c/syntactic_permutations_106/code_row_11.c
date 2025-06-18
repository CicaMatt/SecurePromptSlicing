/*
 * Author: Your Name
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void) {
    char *secret = "Top Secret";
    int fd;
    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
    struct stat st = {0};

    fd = open("file.txt", O_WRONLY | O_CREAT, mode);
    if (fd == -1) {
        printf("Failed to create file\n");
        return 1;
    }

    write(fd, secret, strlen(secret));
    close(fd);

    /* Get the current permissions of the file */
    fstat(fd, &st);

    /* Print the name of the file to the screen */
    printf("File: %s\n", "file.txt");

    return 0;
}