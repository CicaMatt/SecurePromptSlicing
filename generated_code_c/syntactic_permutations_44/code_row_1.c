#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
 
// Define the name of the file to be read as a constant
#define FILENAME "/safe/file.txt"
 
// Declare the main function with an integer argument and an array of character pointers as arguments, respectively
int main(int argc, char *argv[]) {
    // Declare a variable to store the file descriptor
    int fd;
    // Declare a variable to store the read buffer
    char buf[1024];
 
    // Open the file in read mode using the open() function. The first argument is the name of the file, and the second argument specifies the flags used by the system call. In this case, we want to read the file, so we pass O_RDONLY as the flag.
    fd = open(FILENAME, O_RDONLY);
 
    // Check if there is an error opening the file using the errno global variable. If it's non-zero, then there was an error.
    if (errno) {
        // Print a message to stderr indicating that there was an error with the file.
        fprintf(stderr, "Error: %d\n", errno);
 
        // Return -1 to indicate that there was an error.
        return -1;
    }
 
    // Loop until there is no more data to read from the file
    while (read(fd, buf, sizeof(buf)) != 0) {
        // Print the contents of the buffer to stdout using the printf() function. The first argument is a format string that specifies how to interpret the subsequent arguments. In this case, we want to print the contents of the buffer as a string, so we pass %s as the format string.
        printf("%s", buf);
    }
 
    // Close the file using the close() function.
    close(fd);
 
    // Return 0 to indicate that there was no error.
    return 0;
}