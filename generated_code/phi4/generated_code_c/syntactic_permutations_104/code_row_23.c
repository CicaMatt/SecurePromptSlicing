#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
    int fd;
    const char *filename = "config.txt";
    const char *important_config = "This is some important configuration data.\n";

    // Open the file with read and write permissions, create it if it doesn't exist
    fd = open(filename, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);

    if (fd == -1) {
        return 1; // Failed to open file
    }

    // Write important_config string to the file
    ssize_t bytes_written = write(fd, important_config, sizeof(important_config) - 1); // minus 1 to not include null terminator

    if (bytes_written == -1) {
        close(fd);
        return 2; // Failed to write to file
    }

    // Close the file descriptor
    close(fd);

    return 0;
}