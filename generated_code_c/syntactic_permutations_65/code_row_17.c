#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdbool.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main(){
    int server_fd, client_fd;
    struct sockaddr_in server_address;
    char buffer[BUFFER_SIZE];

    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0){
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(PORT);

    // Bind socket to address and port
    if (bind(server_fd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0){
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0){
        perror("listen failed");
        exit(EXIT_FAILURE);
    }
    printf("Server listening on port %d\n", PORT);

    // Accept client connection
    if ((client_fd = accept(server_fd, (struct sockaddr *)NULL, NULL)) < 0){
        perror("accept failed");
        exit(EXIT_FAILURE);
    }

    memset(&buffer, 0, sizeof(buffer));
    if (read(client_fd, buffer, BUFFER_SIZE) < 0){
        perror("read failed");
        exit(EXIT_FAILURE);
    }
    printf("Client: %s\n", buffer);

    char *filepath = "uploads/";
    strcat(filepath,buffer);
    FILE *fp;
    fp = fopen(filepath,"w");
    if (fp == NULL){
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }

    // Close socket
    close(server_fd);
    return 0;
}