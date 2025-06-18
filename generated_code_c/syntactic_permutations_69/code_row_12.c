#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

void upload_image(char* filename, char* image) {
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        printf("Failed to create file\n");
        return;
    }

    write(fd, image, strlen(image));
    close(fd);
}