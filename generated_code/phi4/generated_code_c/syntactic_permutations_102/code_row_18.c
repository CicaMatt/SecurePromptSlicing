#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int fd;
    const char *filename = "important_config";
    const char *text = "important_config\n";

    // Open or create the file with specified permissions
    fd = open(filename, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IROTH);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    // Write to the file
    ssize_t bytes_written = write(fd, text, sizeof(text) - 1); // Subtracting 1 to avoid writing '\0'
    if (bytes_written == -1) {
        perror("write");
        close(fd);
        return 1;
    }

    // Close the file descriptor
    if (close(fd) == -1) {
        perror("close");
        return 1;
    }

    return 0;
}