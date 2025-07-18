#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>

int main(void)
{
    int fd;
    const char *filename = "important_config";
    const char *str = "important_config";
    char buffer[256];

    fd = open(filename, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fd == -1)
    {
        perror("Failed to open file");
        return 1;
    }

    write(fd, str, strlen(str));
    close(fd);

    fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        perror("Failed to open file");
        return 1;
    }

    while (read(fd, buffer, sizeof(buffer)) > 0)
    {
        printf("%s", buffer);
    }

    close(fd);

    return 0;
}