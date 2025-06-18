#include <fcntl.h>

int main(void) {
    int fd;
    char *filename = "test.txt";
    fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY | O_EXCL, 0644);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    return 0;
}