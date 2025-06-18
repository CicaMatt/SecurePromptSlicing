#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
int main() {
    int fd = open("important_config", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR | S_IROTH);
    write(fd, "important_config", 16);
}