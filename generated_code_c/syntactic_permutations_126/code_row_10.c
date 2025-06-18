// Server side C code to demonstrate Server-side programming
// Note that this may not be a complete code and is for demonstration purpose only
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "http_hello_page.h"
 
int main() {
    // Creating the server socket
    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
 
    struct sockaddr_in server_address;
    bzero(&server_address, sizeof(server_address));
 
    // Filling the details to assign an IP address and port number to the socket
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8081);
    server_address.sin_addr.s_addr = INADDR_ANY;
 
    // Bind the socket to a particular IP address and port number using the bind() function.
    bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address));
 
    int request_socket;
    listen(server_socket, 5);
    char buffer[1024] = {0};
 
    // Accepting the incoming connection from the client side using accept() function.
    while (request_socket = accept(server_socket, NULL, NULL))
    {
        // Reading data into buffer from the client side
        read(request_socket, buffer, 1024);
 
        char *requested_url = strstr(buffer, "http://localhost:8081/hello");
        if (requested_url != NULL)
        {
            // Extracting the username from request_body
            char *request_body = strstr(buffer, "\n\n");
            int user_name_length = 0;
 
            while (*request_body++ != '=')
                user_name_length++;
            char username[user_name_length];
 
            // Copying the username from request body to a new variable username
            strncpy(username, request_body, user_name_length);
 
            // Preparing the response message that is to be sent back to the client side
            char outputbuf[2048];
            sprintf(outputbuf, "HTTP/1.1 200 OK\nContent-Type: text/html\n\n<html><body>Hello %s!</body></html>", username);
 
            // Writing the response message to the client side using write()
            write(request_socket, outputbuf, strlen(outputbuf));
        }
    }
}