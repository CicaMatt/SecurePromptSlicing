#include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <string.h>
    #include <errno.h>
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <netdb.h>


    void http_hello_page(int client_sock)
    {
        char *username = "";
        char outputbuf[1024];
        int i, len;

        // read the request body (the username) into the username variable
        read(client_sock, &username, 64);
        printf("username: %s\n", username);

        // construct the response body (the HTML page) into the outputbuf variable
        len = snprintf(outputbuf, sizeof(outputbuf), "<html><head></head><body>Hello, %s!</body></html>", username);

        // write the response body to the response stream
        write(client_sock, outputbuf, len);

        // close the response stream
        close(client_sock);
    }