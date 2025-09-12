#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define UPLOADS_DIR "uploads"

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    int bytes_received;
    FILE *file = NULL;

    while ((bytes_received = recv(client_socket, buffer, sizeof(buffer), 0)) > 0) {
        if (strstr(buffer, "POST /upload") != NULL) {
            const char *boundary_start = "--";
            const char *content_disposition = "Content-Disposition: form-data; name=\"file\"; filename=\"";
            const char *pdf_extension = ".pdf";

            int boundary_pos = 0;
            while ((boundary_pos = strstr(buffer + boundary_pos, boundary_start) - buffer) != -1) {
                if (strstr(buffer + boundary_pos + strlen(boundary_start), content_disposition) != NULL) {
                    char *filename_start = strstr(buffer + boundary_pos, content_disposition);
                    filename_start += strlen(content_disposition);

                    char *filename_end = strchr(filename_start, '"');
                    int filename_len = filename_end - filename_start;
                    char filename[filename_len + 1];
                    strncpy(filename, filename_start, filename_len);
                    filename[filename_len] = '\0';

                    if (strstr(filename, pdf_extension) != NULL) {
                        char filepath[256];
                        snprintf(filepath, sizeof(filepath), "%s/%s", UPLOADS_DIR, filename);
                        file = fopen(filepath, "wb");
                        break;
                    }
                }
                boundary_pos += strlen(boundary_start);
            }

            if (file != NULL) {
                const char *data_start_marker = "\r\n\r\n";
                const char *data_end_marker = "--";

                int data_start_pos = strstr(buffer, data_start_marker) - buffer + strlen(data_start_marker);
                int data_end_pos = strstr(buffer + data_start_pos, data_end_marker) - buffer;

                if (data_start_pos != -1 && data_end_pos != -1) {
                    fwrite(buffer + data_start_pos, 1, data_end_pos - data_start_pos, file);
                }

                while ((bytes_received = recv(client_socket, buffer, sizeof(buffer), 0)) > 0) {
                    int end_pos = strstr(buffer, data_end_marker) - buffer;
                    if (end_pos != -1) {
                        fwrite(buffer, 1, end_pos, file);
                        break;
                    }
                    fwrite(buffer, 1, bytes_received, file);
                }

                fclose(file);
                send(client_socket, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nFile uploaded successfully.", strlen("HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nFile uploaded successfully."), 0);
            } else {
                send(client_socket, "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nInvalid file format.", strlen("HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nInvalid file format."), 0);
            }
        } else {
            send(client_socket, "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nNot found.", strlen("HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nNot found."), 0);
        }
    }

    close(client_socket);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if (mkdir(UPLOADS_DIR, 0755) == -1 && errno != EEXIST) {
        perror("Failed to create uploads directory");
        exit(EXIT_FAILURE);
    }

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

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

    printf("Server listening on port %d...\n", PORT);

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("Accept failed");
            continue;
        }
        handle_client(new_socket);
    }

    close(server_fd);
    return 0;
}