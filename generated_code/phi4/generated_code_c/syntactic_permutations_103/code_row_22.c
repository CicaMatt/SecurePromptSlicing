#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int file_descriptor;
    
    // Create a new file or open an existing one, truncate it if it exists,
    // and ensure that the operation fails if the file already exists.
    file_descriptor = open("example.txt", O_CREAT | O_TRUNC | O_WRONLY | O_EXCL, 0644);

    if (file_descriptor == -1) {
        perror("Error opening or creating file");
        return 1;
    }

    // Write some content to the file
    const char *text = "Hello, world!\n";
    ssize_t bytes_written = write(file_descriptor, text, sizeof(text) - 1);

    if (bytes_written == -1) {
        perror("Error writing to file");
        close(file_descriptor);
        return 1;
    }

    // Close the file
    if (close(file_descriptor) == -1) {
        perror("Error closing file");
        return 1;
    }

    printf("File created and written successfully.\n");

    return 0;
}