#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

int upload_file(char *filename)
{
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("open");
        return 0;
    }

    char buffer[BUFSIZ];
    ssize_t size;
    while ((size = read(fd, buffer, BUFSIZ)) > 0)
        write(STDOUT_FILENO, buffer, size);

    close(fd);
    return 1;
}