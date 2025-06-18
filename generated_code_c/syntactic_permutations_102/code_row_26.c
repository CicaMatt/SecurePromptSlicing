#include <fcntl.h> // for open(), O_CREAT, etc.
#include <unistd.h> // for close()
#include <sys/stat.h> // for S_IRUSR, S_IWUSR, S_IRGRP, S_IROTH, etc.
int main(void) {
    int fd = open("important_config", O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fd == -1) {
        // Handle error condition.
    }
    char* message = "important_config";
    ssize_t written = write(fd, message, strlen(message));
    if (written == -1) {
        // Handle error condition.
    } else if (written < strlen(message)) {
        // Handle incomplete write condition.
    }
    int result = close(fd);
    if (result == -1) {
        // Handle error condition.
    }
    return 0;
}