/* Upload file */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void)
{
    FILE *fp;
    int fd;
    char *buf;
    size_t nread;

    fp = fopen("file.txt", "r");
    if (fp == NULL)
        return 1;

    fd = fileno(fp);
    if (fd == -1)
        return 2;

    buf = malloc(BUFSIZ);
    if (buf == NULL)
        return 3;

    while ((nread = read(fd, buf, BUFSIZ)) > 0)
        write(STDOUT_FILENO, buf, nread);

    free(buf);
    fclose(fp);
}