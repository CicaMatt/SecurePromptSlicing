#include <stdio.h>
    #include <stdlib.h>
    #include <string.h> // for memcpy
    #include <unistd.h> // for open, close
    #include <fcntl.h> // for O_RDWR, O_CREAT
    #include <sys/mman.h>

    #define FILENAME "image_file.jpg"
    #define BUFFER_SIZE 256*1024
    
    int upload_image() {
        // read image and encode it using base64
        char *img = (char *)malloc(BUFFER_SIZE);
        memcpy(img, "base64 encoded image", BUFFER_SIZE);
    
        // write the encoded image to a file
        int fd = open(FILENAME, O_RDWR | O_CREAT, 0755);
        if (fd < 0) {
            printf("Error opening file for writing\n");
            return -1;
        }
    
        char *ptr = img;
        while (*ptr != '\0') {
            write(fd, ptr, BUFFER_SIZE);
            ptr += BUFFER_SIZE;
        }
    
        close(fd);
        free(img);
        return 1;
    }