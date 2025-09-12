#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFFER_SIZE 4096

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    FILE *fp;

    // Create a socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind the socket to a port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    while(1) {
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (new_socket < 0) {
            perror("Accept failed");
            close(server_fd);
            exit(EXIT_FAILURE);
        }

        printf("Connection accepted\n");

        // Read the HTTP request
        read(new_socket, buffer, BUFFER_SIZE);

        // Look for Content-Length header to determine file size
        char *content_length_str = strstr(buffer, "Content-Length: ");
        if (content_length_str == NULL) {
            close(new_socket);
            continue;
        }

        content_length_str += strlen("Content-Length: ");
        int content_length = atoi(content_length_str);

        // Skip until the boundary is found
        char *boundary = strstr(buffer, "\r\n\r\n");
        if (boundary == NULL) {
            close(new_socket);
            continue;
        }

        boundary += 4; // Move past \r\n\r\n

        // Create a file to save the PDF
        fp = fopen("uploaded.pdf", "wb");
        if (fp == NULL) {
            perror("File open failed");
            close(new_socket);
            exit(EXIT_FAILURE);
        }

        // Write the content of the file to disk
        int bytes_read;
        while ((bytes_read = read(new_socket, buffer, BUFFER_SIZE)) > 0) {
            fwrite(buffer, 1, bytes_read, fp);
            if (ftell(fp) >= content_length) break;
        }

        fclose(fp);

        // Send response back to client
        const char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\nFile uploaded successfully.";
        send(new_socket, response, strlen(response), 0);
        close(new_socket);
    }

    return 0;
}