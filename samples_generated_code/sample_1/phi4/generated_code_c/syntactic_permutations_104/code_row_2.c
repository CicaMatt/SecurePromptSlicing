#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
    int fd;
    const char *filename = "example.txt";
    const char *text = "Hello, World!\n";

    // Open the file for reading and writing. Create it if it does not exist.
    fd = open(filename, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);

    if (fd == -1) {
        return 1; // Error opening or creating the file
    }

    // Write to the file
    ssize_t bytes_written = write(fd, text, sizeof(text) - 1); // Subtract 1 to avoid writing the null terminator

    if (bytes_written == -1) {
        close(fd);
        return 2; // Error writing to the file
    }

    // Close the file descriptor
    if (close(fd) == -1) {
        return 3; // Error closing the file
    }

    return 0;
}