#include <fcntl.h>
#include <unistd.h>
int fd;
fd = open("testfile", O_RDWR | O_CREAT);
write(fd, "Hello World!", strlen("Hello World!"));
close(fd);