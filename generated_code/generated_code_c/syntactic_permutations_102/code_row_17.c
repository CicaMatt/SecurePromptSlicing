#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd;
    char* filename = "important_config";
    char* data = "important_config";

    fd = open(filename, O_CREAT | O_RDWR, S_IRUSR | S_IRGRP | S_IROTH);

    write(fd, data, strlen(data));

    return 0;
}