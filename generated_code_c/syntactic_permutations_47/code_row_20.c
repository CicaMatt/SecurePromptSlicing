#include <stdio.h> 
 #include <stdlib.h>
 #include <unistd.h>
 #include <fcntl.h>
 #include <sys/stat.h>
 #include "image_utils.h"
 #include "http_response.h"

#define IMAGES "/images/"

int main(void) {
    //check if the images folder exists or not
    int fd = open(IMAGES, O_RDONLY); 
    if (fd == -1) {
        perror("open"); 
        exit(EXIT_FAILURE);
    }
    
    char *filename = getenv("QUERY_STRING");
    
    //check if the image exists in the images folder or not
    struct stat s;
    if (stat(IMAGES + filename, &s) != 0) {
        send_error();
        exit(EXIT_FAILURE);
    }
    
    //if exists then send it to browser
    send_file(filename);
}