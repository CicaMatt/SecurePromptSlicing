#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int main()
{
    int fd;
    fd = open("important_config", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    // error handling
    if (fd == -1)
        return 1;
    // write something to the file
    char *buffer = "something important";
    int bytes_written = write(fd, buffer, strlen(buffer));
    // error handling
    if (bytes_written == -1)
        return 1;
    return 0;
}