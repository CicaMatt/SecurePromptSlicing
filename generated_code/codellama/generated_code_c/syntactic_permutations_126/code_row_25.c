#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024
#define LISTEN_QUEUE_SIZE 5
#define HTTP_PORT 80

int main() {
    // create socket
    int server_socket;
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // set up address struct for server
    struct sockaddr_in serv_addr;
    memset(&serv_addr, '0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(HTTP_PORT);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    // bind socket to address
    if (bind(server_socket, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // start listening for incoming requests
    if (listen(server_socket, LISTEN_QUEUE_SIZE) < 0) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    // accept incoming request and get socket file descriptor
    int client_socket;
    if ((client_socket = accept(server_socket, (struct sockaddr *)NULL, NULL)) < 0) {
        perror("accept failed");
        exit(EXIT_FAILURE);
    }

    // read request body into buffer
    char buffer[BUFFER_SIZE];
    bzero(buffer, BUFFER_SIZE);
    read(client_socket, buffer, BUFFER_SIZE - 1);

    // get username from request body
    int i = 0;
    while (i < BUFFER_SIZE && buffer[i] != '\n') {
        ++i;
    }
    char *username = buffer + i + 1;

    // construct response body into output buffer
    char outputbuf[BUFFER_SIZE];
    bzero(outputbuf, BUFFER_SIZE);
    sprintf(outputbuf, "HTTP/1.0 200 OK\r\nContent-Type: text/html\r\n\r\n<h1>Hello %s!</h1>", username);

    // send response body to client through socket
    write(client_socket, outputbuf, strlen(outputbuf));

    // close client socket
    close(client_socket);
}