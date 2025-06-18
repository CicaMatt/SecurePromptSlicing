// header file for standard library functions, constants, and types.
#include <stdio.h> 
// header file for various types and macros used in socket programming.
#include <netdb.h> 
// header file for I/O operations on sockets.
#include <sys/socket.h> 
// header file for working with strings.
#include <string.h> 
// header file for standard library functions, constants, and types.
#include <stdlib.h> 
// header file for Unix-style time functions.
#include <time.h> 
// header file for manipulating file descriptors.
#include <unistd.h>
// header file for working with network sockets.
#include <arpa/inet.h>

int redirect_invalid_url(char * url) {
    // check if the URL has domain example.com
    int isValid = strstr(url, "example.com") != NULL; 
    
    // if it is not valid, return an error message
    if (!isValid) {
        printf("Invalid URL");
        return -1;
    }
    
    // if it is valid, redirect the user to the URL
    printf("Redirecting to %s", url);
    return 0;
}