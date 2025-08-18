#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define UPLOAD_DIR "./uploads"

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    int bytes_received;
    FILE *file;

    while ((bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0)) > 0) {
        if (strstr(buffer, "Content-Disposition: form-data; name=\"file\"; filename=\"") != NULL) {
            char *filename_start = strstr(buffer, "filename=\"") + strlen("filename=\"");
            char *filename_end = strchr(filename_start, '\"');
            int filename_length = filename_end - filename_start;
            char filename[filename_length + 1];
            strncpy(filename, filename_start, filename_length);
            filename[filename_length] = '\0';

            // Create uploads directory if it does not exist
            mkdir(UPLOAD_DIR, 0755);

            file = fopen(strcat(UPLOAD_DIR, "/" , filename), "w");
            if (file == NULL) {
                perror("Failed to create file");
                close(client_socket);
                return;
            }

            // Skip headers
            while ((bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0)) > 0 && strncmp(buffer, "\r\n", 2) != 0) {}

            // Write content to file
            while (1) {
                bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0);
                if (bytes_received <= 0) break;
                fwrite(buffer, 1, bytes_received, file);
                if (strstr(buffer, "\r\n") != NULL) break;
            }
            fclose(file);
        } else {
            // Send HTTP response
            const char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\nFile uploaded successfully.";
            send(client_socket, response, strlen(response), 0);
        }
    }

    close(client_socket);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("Setsockopt failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("Accept failed");
            close(server_fd);
            exit(EXIT_FAILURE);
        }
        handle_client(new_socket);
    }

    return 0;
}