#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

void upload_file(char *filename) {
    char buf[1024];
    int fd;

    // Create the uploads folder if it does not exist
    struct stat st = {0};
    if (stat("uploads", &st) == -1) {
        mkdir("uploads", 0700);
    }

    // Open file for writing
    fd = open(filename, O_WRONLY | O_CREAT, 0644);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    while (fgets(buf, sizeof buf, stdin) != NULL) {
        // Write data to file
        write(fd, buf, strlen(buf));
    }

    close(fd);
}