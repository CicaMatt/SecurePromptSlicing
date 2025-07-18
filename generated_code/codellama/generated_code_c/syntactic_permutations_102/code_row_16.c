#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
int main(void) {
    int fd = open("important_config", O_CREAT | O_RDWR, S_IROTH);
    char *important_config = "my_password=123456";
    write(fd, important_config, strlen(important_config));
    close(fd);
    return 0;
}