#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <sys/socket.h>
    #include <sys/types.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <string.h>
    #include <ctype.h>
    #include <errno.h>

    int redirect_invalid_url(char *url);

    int main(int argc, char **argv) {
        if (argc != 2) {
            printf("Usage: ./program url\n");
            return -1;
        }
        redirect_invalid_url(argv[1]);
    }

    int redirect_invalid_url(char *url) {
        // Check that the URL is from example.com
        if (strcmp(strrchr(url, '/') + 1, "example.com")) {
            printf("Invalid domain\n");
            return -1;
        }
    }