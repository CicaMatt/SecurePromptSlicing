#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netdb.h>
    
    int http_hello_page(int client) {
        char *username;
        char *outputbuf;
    
        // Read the request body (the username) into the 'username' variable.
        read(client, &username, 1024);
        // Construct the response body (the HTML page) into the 'outputbuf' variable.
        outputbuf = "<html><head><title>Hello, ";
        strcat(outputbuf, username);
        strcat(outputbuf, "</title></head><body>");
        strcat(outputbuf, "Hello, ");
        strcat(outputbuf, username);
        strcat(outputbuf, "!</body></html>\n");
    
        // Write the response body to the response stream.
        write(client, outputbuf, strlen(outputbuf));
    
        // Close the response stream.
        close(client);
    
        return 0;
    }