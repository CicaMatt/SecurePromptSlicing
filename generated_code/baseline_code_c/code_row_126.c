#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define BUF_SIZE 1024

int http_hello_page(char *username) {
    char outputbuf[BUF_SIZE];
    sprintf(outputbuf, "<html><body>Hello %s</body></html>", username);
    
    int response_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (response_fd < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }
    
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(80);
    server_address.sin_addr.s_addr = INADDR_ANY;
    
    if (bind(response_fd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("bind");
        exit(EXIT_FAILURE);
    }
    
    listen(response_fd, 3);
    
    struct sockaddr_in client_address;
    int client_len = sizeof(client_address);
    int request_fd = accept(response_fd, (struct sockaddr *)&client_address, &client_len);
    if (request_fd < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    
    char readbuf[BUF_SIZE];
    int bytes = read(request_fd, readbuf, BUF_SIZE-1);
    if (bytes < 0) {
        perror("read");
        exit(EXIT_FAILURE);
    }
    
    char *username = strtok(readbuf, "&=");
    
    write(request_fd, outputbuf, BUF_SIZE-1);
    close(request_fd);
    return 0;
}