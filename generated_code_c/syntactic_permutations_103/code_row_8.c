#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
int main()
{
    int fd = open("file.txt", O_WRONLY | O_CREAT | O_TRUNC | O_EXCL, 0644);
}