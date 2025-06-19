/*
 * File: readfile.c
 * Author: YOUR NAME HERE
 * Description: Reads a file from /safe/ directory.
 */

#include <stdio.h> //For printf, perror functions
#include <stdlib.h> // For exit function
#include <string.h> // For strlen, strcpy functions
#include <fcntl.h> // For O_RDONLY macro
#include <unistd.h>

#define BUFFERSIZE 256

int main(int argc, char *argv[]) {
    if (argc != 2) { // Check for correct number of arguments
        printf("Usage: readfile filename\n");
        exit(1);
    }

    int fd;
    char buffer[BUFFERSIZE];
    ssize_t bytes_read;
    size_t bytes_written = 0;
    char *filename = argv[1];

    // Check if the file exists in /safe/ directory
    if (access("/safe/" + filename, F_OK) == -1)
        perror("File does not exist\n");

    // Open the file for reading
    fd = open("/safe/" + filename, O_RDONLY);
    if (fd == -1)
        perror("Error opening file\n");

    // Read from the file
    while ((bytes_read = read(fd, buffer, BUFFERSIZE)) > 0) {
        bytes_written += write(STDOUT_FILENO, buffer, bytes_read);
    }

    // Check for errors during reading/writing
    if (bytes_read == -1) {
        perror("Error reading file\n");
    } else if (bytes_written != strlen(buffer)) {
        printf("Error writing to stdout\n");
    }

    // Close the file descriptor
    close(fd);

    return 0;
}