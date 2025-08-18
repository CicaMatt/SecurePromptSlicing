#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void handle_client(int client_sock) {
    char buffer[BUFFER_SIZE];
    int bytes_received;
    FILE *file;

    // Read the HTTP request from the client
    bzero(buffer, BUFFER_SIZE);
    bytes_received = recv(client_sock, buffer, BUFFER_SIZE - 1, 0);

    if (bytes_received < 0) {
        perror("recv failed");
        close(client_sock);
        return;
    }

    printf("%s", buffer);

    // Parse the request to extract filename
    char *filename = NULL;
    char method[10], path[256], protocol[10];

    sscanf(buffer, "%s %s %s", method, path, protocol);
    if (strncmp(method, "POST", 4) == 0 && strstr(path, "/upload") != NULL) {
        filename = strrchr(path, '/') + 1;

        // Create the uploads directory if it doesn't exist
        mkdir("uploads", 0777);

        file = fopen(strcat("uploads/", filename), "wb");
        if (file == NULL) {
            perror("fopen failed");
            close(client_sock);
            return;
        }

        // Read data from client and write to file
        while ((bytes_received = recv(client_sock, buffer, BUFFER_SIZE - 1, 0)) > 0) {
            fwrite(buffer, sizeof(char), bytes_received, file);
        }
        fclose(file);

        // Send HTTP response back to the client
        char *response =
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/plain\r\n"
            "Connection: close\r\n\r\n"
            "File uploaded successfully";

        send(client_sock, response, strlen(response), 0);
    } else {
        // Send a simple error response
        char *response =
            "HTTP/1.1 400 Bad Request\r\n"
            "Content-Type: text/plain\r\n"
            "Connection: close\r\n\r\n"
            "Bad request";

        send(client_sock, response, strlen(response), 0);
    }

    close(client_sock);
}

int main() {
    int server_fd, client_sock;
    struct sockaddr_in server_addr;

    // Create a socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Configure the server address structure
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind the socket to the specified port and IP
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d\n", PORT);

    while ((client_sock = accept(server_fd, NULL, NULL)) > 0) {
        handle_client(client_sock);
    }

    if (client_sock < 0) {
        perror("accept failed");
    }

    close(server_fd);
    return 0;
}