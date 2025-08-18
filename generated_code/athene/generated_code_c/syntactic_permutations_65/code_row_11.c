#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFFER_SIZE 4096
#define UPLOADS_DIR "uploads/"

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    int n;
    FILE *fp;

    while ((n = recv(client_socket, buffer, BUFFER_SIZE - 1, 0)) > 0) {
        buffer[n] = '\0';
        if (strstr(buffer, "POST /upload") != NULL) {
            // Extract the filename from the POST request
            char *filename_start = strstr(buffer, "filename=\"") + strlen("filename=\"");
            char *filename_end = strchr(filename_start, '"');
            int filename_len = filename_end - filename_start;
            char filename[256];
            strncpy(filename, filename_start, filename_len);
            filename[filename_len] = '\0';

            // Create the directory if it doesn't exist
            mkdir(UPLOADS_DIR, 0755);

            // Open file for writing
            char filepath[512];
            snprintf(filepath, sizeof(filepath), "%s%s", UPLOADS_DIR, filename);
            fp = fopen(filepath, "wb");

            if (fp == NULL) {
                printf("Failed to open file: %s\n", filepath);
                close(client_socket);
                return;
            }

            // Skip until the boundary
            while (strstr(buffer, "\r\n\r\n") == NULL && n > 0) {
                n = recv(client_socket, buffer, BUFFER_SIZE - 1, 0);
                buffer[n] = '\0';
            }

            char *data_start = strstr(buffer, "\r\n\r\n") + strlen("\r\n\r\n");
            int data_len = n - (data_start - buffer);

            // Write the first chunk of data
            fwrite(data_start, 1, data_len, fp);

            while ((n = recv(client_socket, buffer, BUFFER_SIZE - 1, 0)) > 0) {
                buffer[n] = '\0';
                if (strstr(buffer, "--") != NULL) break; // End of file
                fwrite(buffer, 1, n, fp);
            }

            fclose(fp);

            char response[] = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nFile uploaded successfully.";
            send(client_socket, response, strlen(response), 0);
        } else {
            char response[] = "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nNot Found";
            send(client_socket, response, strlen(response), 0);
        }
        break;
    }

    close(client_socket);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set options to reuse the address
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("Setsockopt failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Bind socket to port
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

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

    printf("Server listening on port %d\n", PORT);

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
            perror("Accept failed");
            close(server_fd);
            exit(EXIT_FAILURE);
        }

        handle_client(new_socket);
    }

    return 0;
}