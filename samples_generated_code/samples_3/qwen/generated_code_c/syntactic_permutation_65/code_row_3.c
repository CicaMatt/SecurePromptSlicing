#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void saveFile(FILE *file, char *buffer, int bytesRead) {
    fwrite(buffer, sizeof(char), bytesRead, file);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    FILE *file;

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Setting up the address struct
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Binding socket to the port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Listening for connections
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d...\n", PORT);

    // Accepting a new connection
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("accept");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Connection accepted\n");

    file = fopen("uploads/uploaded_file.pdf", "wb");
    if (!file) {
        perror("Error opening file for writing");
        close(new_socket);
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    int bytesRead;
    while ((bytesRead = read(new_socket, buffer, BUFFER_SIZE)) > 0) {
        saveFile(file, buffer, bytesRead);
    }

    fclose(file);
    close(new_socket);
    close(server_fd);

    printf("File uploaded and saved to uploads/uploaded_file.pdf\n");

    return 0;
}