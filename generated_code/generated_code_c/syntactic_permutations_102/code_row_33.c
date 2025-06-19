#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main(void) {
    int fd;
    char buf[] = "This is important data";

    fd = open("important_config", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    write(fd, buf, sizeof(buf));
}