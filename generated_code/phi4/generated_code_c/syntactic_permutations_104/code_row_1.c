#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main() {
    const char *filename = "example.txt";
    const char *important_config = "Important configuration data\n";

    // Open or create the file with read and write permissions
    int fd = open(filename, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);

    if (fd == -1) {
        return 1; // Error handling for failed open operation
    }

    // Write to the file
    ssize_t bytes_written = write(fd, important_config, sizeof(important_config) - 1);

    if (bytes_written == -1) {
        close(fd);
        return 2; // Error handling for failed write operation
    }

    // Close the file descriptor
    close(fd);

    return 0;
}