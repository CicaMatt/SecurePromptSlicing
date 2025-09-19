#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080

void handle_client(int client_socket) {
    char buffer[1024] = {0};
    int read_size;
    FILE *fp;

    // Read the HTTP request from the client
    read_size = recv(client_socket, buffer, sizeof(buffer), 0);

    if (read_size < 1) {
        close(client_socket);
        return;
    }

    printf("Received: %s\n", buffer);

    char method[10];
    sscanf(buffer, "%s ", method);

    // Check if the request is a POST request
    if (strcmp(method, "POST") == 0) {
        char boundary[1024] = {0};
        char *boundary_start = strstr(buffer, "boundary=");
        if (boundary_start) {
            sscanf(boundary_start + strlen("boundary="), "%s", boundary);
        }

        // Find the start of the file data
        char *file_data_start = strstr(buffer, "\r\n\r\n") + 4;
        int content_length = 0;

        // Extract Content-Length header
        char *content_length_start = strstr(buffer, "Content-Length: ");
        if (content_length_start) {
            sscanf(content_length_start + strlen("Content-Length: "), "%d", &content_length);
        }

        // Prepare to receive the file data
        int remaining_size = content_length;
        char *file_data = malloc(remaining_size);

        while (remaining_size > 0) {
            read_size = recv(client_socket, file_data + (content_length - remaining_size), 
                             remaining_size, 0);
            if (read_size < 1) break;
            remaining_size -= read_size;
        }

        // Save the file to the uploads directory
        char filename[256] = "uploads/uploaded_file.pdf";
        mkdir("uploads", 0777);

        fp = fopen(filename, "wb");
        if (fp == NULL) {
            perror("Failed to open file for writing");
            free(file_data);
            close(client_socket);
            return;
        }

        fwrite(file_data + strlen(boundary) + 4, 1, content_length - strlen(boundary) - 4, fp);
        fclose(fp);

        printf("File saved as %s\n", filename);
    } else {
        // Handle non-POST requests
        char *response = "HTTP/1.1 405 Method Not Allowed\r\nContent-Type: text/html\r\n\r\n"
                         "<html><body><h1>Method Not Allowed</h1></body></html>";
        send(client_socket, response, strlen(response), 0);
    }

    free(file_data);
    close(client_socket);
}

int main() {
    int server_fd, client_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    while (1) {
        if ((client_socket = accept(server_fd, (struct sockaddr *)&address, 
                                   (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            close(server_fd);
            exit(EXIT_FAILURE);
        }

        handle_client(client_socket);
    }

    return 0;
}