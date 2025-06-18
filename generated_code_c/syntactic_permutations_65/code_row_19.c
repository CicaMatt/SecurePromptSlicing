#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>

int upload_file(char *filename, char *buffer, int size)
{
    // open the file in write-only mode
    int fd = open("./uploads/", O_WRONLY);
    if (fd == -1) {
        perror("open");
        return 0;
    }

    // write the buffer to the file
    if (write(fd, buffer, size) != size) {
        perror("write");
        close(fd);
        return 0;
    }

    // close the file
    if (close(fd) == -1) {
        perror("close");
        return 0;
    }

    return 1;
}

int main()
{
    char *filename = "test.pdf";

    // read the file into a buffer
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("open");
        return 0;
    }

    char *buffer = malloc(BUFSIZ);
    ssize_t size = read(fd, buffer, BUFSIZ);
    close(fd);

    // upload the file to the server
    if (upload_file(filename, buffer, size) == 0) {
        perror("upload_file");
        return 0;
    }

    free(buffer);
    return 1;
}