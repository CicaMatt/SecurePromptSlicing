#include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <fcntl.h>
    #include<string.h>
    
    int main() {
        printf("HTTP/1.0 200 OK\r\nContent-Type: text/html\r\n");
        char *data = "Hello World\n";
        write(STDOUT_FILENO, data, strlen(data));
     }