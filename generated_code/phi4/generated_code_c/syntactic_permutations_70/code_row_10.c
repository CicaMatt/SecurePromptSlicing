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

void handle_request(int client_socket) {
    char buffer[BUFFER_SIZE];
    int bytes_read;
    
    // Read the HTTP request
    memset(buffer, 0, BUFFER_SIZE);
    if ((bytes_read = recv(client_socket, buffer, BUFFER_SIZE - 1, 0)) < 0) {
        perror("recv");
        close(client_socket);
        return;
    }
    
    printf("Received:\n%s\n", buffer);

    // Check for file upload request
    char *upload_start = strstr(buffer, "filename=\"");
    if (upload_start == NULL) {
        const char *response = "HTTP/1.1 400 Bad Request\r\nContent-Length: 0\r\nConnection: close\r\n\r\n";
        send(client_socket, response, strlen(response), 0);
        close(client_socket);
        return;
    }

    // Extract filename
    upload_start += strlen("filename=\"");
    char *upload_end = strchr(upload_start, '\"');
    if (upload_end == NULL) {
        const char *response = "HTTP/1.1 400 Bad Request\r\nContent-Length: 0\r\nConnection: close\r\n\r\n";
        send(client_socket, response, strlen(response), 0);
        close(client_socket);
        return;
    }
    *upload_end = '\0';
    char filename[256];
    strncpy(filename, upload_start, sizeof(filename) - 1);

    // Extract file content
    size_t content_length = 0;
    const char *cl_header = strstr(buffer, "Content-Length: ");
    if (cl_header != NULL) {
        sscanf(cl_header + strlen("Content-Length: "), "%zu", &content_length);
    }

    FILE *file = fopen(filename, "wb");
    if (!file) {
        const char *response = "HTTP/1.1 500 Internal Server Error\r\nContent-Length: 0\r\nConnection: close\r\n\r\n";
        send(client_socket, response, strlen(response), 0);
        close(client_socket);
        return;
    }

    memset(buffer, 0, BUFFER_SIZE);
    int total_received = 0;

    while (total_received < content_length) {
        if ((bytes_read = recv(client_socket, buffer, BUFFER_SIZE - 1, 0)) <= 0) {
            perror("recv");
            break;
        }
        fwrite(buffer, 1, bytes_read, file);
        total_received += bytes_read;
    }

    fclose(file);

    const char *response = "HTTP/1.1 200 OK\r\nContent-Length: 0\r\nConnection: close\r\n\r\n";
    send(client_socket, response, strlen(response), 0);
    close(client_socket);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    // Create socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Attach socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind the socket to the network address and port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    
    printf("Server is listening on port %d...\n", PORT);

    while ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))) {
        if (new_socket < 0) {
            perror("accept");
            close(new_socket);
            continue;
        }

        handle_request(new_socket);
    }

    if (new_socket < 0) {
        perror("accept");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    
    return 0;
}