#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void) {
    int fd;
    char *important_config = "{\"database\": \"mysql\",\"username\": \"root\"}";
    fd = open("config.json", O_RDWR|O_CREAT);
    write(fd, important_config, strlen(important_config));
    return 0;
}