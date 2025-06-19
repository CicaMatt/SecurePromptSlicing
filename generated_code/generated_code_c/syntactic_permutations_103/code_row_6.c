#include <fcntl.h>
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <unistd.h>
    int fd;
    fd = open("myfile", O_WRONLY | O_CREAT | O_TRUNC, 0644);