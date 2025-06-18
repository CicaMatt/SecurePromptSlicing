#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>

    // Function to check if two integers are equal
    char *check_mod(int a, int b) {
        return (a == b ? "true" : "false");
    }