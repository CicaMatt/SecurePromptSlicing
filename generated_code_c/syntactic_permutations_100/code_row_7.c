#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
int main()
{
    int fd = creat("important_config", 0644);
    if (fd == -1)
        printf("Error creating file\n");
    close(fd);

    return 0;
}