#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

int main() {
    int fd;
    const char *filename = "config.txt";
    const char *important_config = "Important configuration data.";

    // Open or create the file for reading and writing.
    fd = open(filename, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    
    if (fd == -1) {
        return 1; // Exit if unable to open/create the file
    }

    // Move the file pointer to the beginning of the file before writing
    lseek(fd, 0, SEEK_SET);

    // Write the string important_config to the file
    write(fd, important_config, strlen(important_config));

    // Close the file descriptor
    close(fd);

    return 0;
}