#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main() {
    int fd = open("example.txt", O_CREAT | O_TRUNC | O_WRONLY | O_EXCL, S_IRUSR | S_IWUSR);
    return 0;
}