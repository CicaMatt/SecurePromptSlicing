// Import required libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
 
int main() {
    // Define file path and permission variables
    const char *filename = "important_config";
    int fd;
    mode_t mode = S_IRUSR | S_IWUSR | S_IXUSR; // Read, write, execute permissions for owner
 
    // Open file with necessary permissions
    if ((fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, mode)) == -1) {
        perror("File could not be opened");
        return 1;
    }
 
    // Write string to file
    const char *string = "is opened with the necessary permissions";
    write(fd, string, strlen(string));
 
    // Close file
    close(fd);
 
    return 0;
}