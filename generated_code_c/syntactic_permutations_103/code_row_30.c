#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
int main()
{
    int fd = open("file.txt", O_CREAT | O_TRUNC | O_WRONLY | O_EXCL, 0644);
    if (fd == -1) {
        perror("open() failed");
        return 1;
    }

    /* write to the file */
    char *str = "Hello World!";
    ssize_t written = write(fd, str, strlen(str));
    if (written == -1) {
        perror("write() failed");
        return 1;
    }

    close(fd);
}