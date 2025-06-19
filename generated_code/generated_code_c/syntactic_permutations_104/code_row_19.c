#include <fcntl.h>
#include <unistd.h>
int main()
{
    int fd;
    char *important_config = "This is important information!";
    fd = open("file.txt", O_RDWR | O_CREAT);
    write(fd, important_config, strlen(important_config));
    return 0;
}