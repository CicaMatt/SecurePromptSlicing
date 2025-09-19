#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define UPLOADS_DIR "uploads"

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    int bytes_received, total_bytes = 0;
    FILE *file = NULL;

    while ((bytes_received = recv(client_socket, buffer, BUFFER_SIZE - 1, 0)) > 0) {
        total_bytes += bytes_received;
        if (total_bytes < 256 && strstr(buffer, "POST /upload HTTP/1.1") != NULL) {
            char *filename_start = strstr(buffer, "filename=");
            if (filename_start == NULL) break;

            filename_start += 9; // Skip "filename="
            char *filename_end = strchr(filename_start, '"');
            if (filename_end == NULL) break;
            *filename_end = '\0';

            char *content_disposition_end = strstr(buffer, "\r\n\r\n");
            if (content_disposition_end == NULL) break;

            int header_length = content_disposition_end - buffer + 4;
            total_bytes -= header_length;

            char filename[BUFFER_SIZE];
            snprintf(filename, sizeof(filename), "%s/%s", UPLOADS_DIR, filename_start);
            file = fopen(filename, "wb");
            if (file == NULL) {
                perror("Failed to open file for writing");
                break;
            }

            content_disposition_end += 4; // Skip "\r\n\r\n"
            bytes_received -= header_length;
            fwrite(content_disposition_end, 1, bytes_received, file);
        } else if (file != NULL) {
            fwrite(buffer, 1, bytes_received, file);
        }
    }

    if (file != NULL) fclose(file);

    const char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nFile uploaded successfully";
    send(client_socket, response, strlen(response), 0);
    close(client_socket);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if (mkdir(UPLOADS_DIR, 0755) != 0 && errno != EEXIST) {
        perror("Failed to create uploads directory");
        return EXIT_FAILURE;
    }

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        return EXIT_FAILURE;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        return EXIT_FAILURE;
    }

    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        return EXIT_FAILURE;
    }

    printf("Server listening on port %d...\n", PORT);

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("Accept failed");
            continue;
        }
        handle_client(new_socket);
    }

    close(server_fd);
    return EXIT_SUCCESS;
}