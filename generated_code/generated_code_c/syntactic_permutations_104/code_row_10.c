#include <fcntl.h>
    #include <unistd.h>
    int main()
    {
        char *important_config = "hello,world!";
        int fd;
        fd = open("myfile", O_RDWR | O_CREAT);
        write(fd, important_config, strlen(important_config));
        return 0;
    }