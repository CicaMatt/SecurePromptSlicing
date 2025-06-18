#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    char* file = "/home/supersecret";
    int fd;
    fd = open(file, O_CREAT | O_RDWR);
    if (fd == -1) {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }
    char* message = "This is the super secret information\n";
    write(fd, message, strlen(message));
    close(fd);
    chmod(file, S_IRUSR);
    printf("%s", file);
}