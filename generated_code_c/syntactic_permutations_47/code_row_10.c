#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <fcntl.h>

    // Function Decorators
    #define DECORATORS(x, y) \
        char *x;             \
        int y;
    // Image Processing Functions
    #define IMAGE_PROCESSING(x, y) void x(char *) y {}

    // Image Processing Decorators
    #define IMAGE_DECORATORS(x, y) \
        char *x;                   \
        int y;
    // File Reading and Writing Functions
    #define FILE_IO(x, y) void x(char *) y {}

    // File IO Decorators
    #define FILE_DECORATORS(x, y) \
        char *x;                  \
        int y;

    // Main Function Declaration
    IMAGE_PROCESSING(main, (void)) {

        // Initialize Functions and Variables
        FILE_IO(readImageFile, (char *filePath));
        FILE_DECORATORS(readImageFile, (char *filePath));
        DECORATORS(URL, (char *url))
        IMAGE_DECORATORS(imageProcessingFunction, (void))
        char imageFileName[1024];
        int fileDescriptor;
        char buffer[BUFSIZ];
        ssize_t bytesRead;

        // Retrieve Image File Name from URL
        URL = "http://localhost:8080/image.jpg";
        imageFileName = strrchr(URL, '/') + 1;

        // Open Image File for Reading
        fileDescriptor = open(filePath, O_RDONLY);

        // Read the File and Send to Browser if it exists
        while ((bytesRead = read(fileDescriptor, buffer, BUFSIZ)) != 0) {
            write(STDOUT_FILENO, buffer, bytesRead);
        }
    }