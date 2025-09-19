#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
    const char *filename = "important_file.txt";
    const char *content = "important_config\n";

    int fd = open(filename, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        return 1; // Error opening the file
    }

    ssize_t bytes_written = write(fd, content, sizeof(content) - 1);
    if (bytes_written == -1) {
        close(fd);
        return 2; // Error writing to the file
    }

    close(fd);
    return 0;
}