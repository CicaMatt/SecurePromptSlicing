#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE] = {0};
    int valread = read(client_socket, buffer, BUFFER_SIZE);
    if (valread <= 0) {
        return;
    }

    // Check for POST request and file upload
    const char *post_start = "POST /upload HTTP/1.1";
    const char *boundary_start = "\r\nContent-Type: multipart/form-data; boundary=";
    const char *filename_start = "filename=\"";
    if (strncmp(buffer, post_start, strlen(post_start)) == 0) {
        const char *boundary_pos = strstr(buffer, boundary_start);
        if (boundary_pos != NULL) {
            boundary_pos += strlen(boundary_start);
            char boundary[256] = {0};
            sscanf(boundary_pos, "%[^'\r\n']", boundary);

            const char *filename_pos = strstr(boundary_pos, filename_start);
            if (filename_pos != NULL) {
                filename_pos += strlen(filename_start);
                char filename[256] = {0};
                sscanf(filename_pos, "%[^'\"']", filename);

                // Create file to write uploaded content
                int file_fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (file_fd == -1) {
                    perror("Failed to create file");
                    return;
                }

                // Find start of file data
                const char *data_start = strstr(filename_pos + strlen(filename), "\r\n\r\n");
                if (data_start != NULL) {
                    data_start += 4; // Move past \r\n\r\n

                    // Write file content to disk
                    while (1) {
                        valread = read(client_socket, buffer, BUFFER_SIZE);
                        if (valread <= 0) break;

                        char *boundary_end = strstr(buffer, boundary);
                        if (boundary_end != NULL) {
                            int data_size = boundary_end - data_start;
                            write(file_fd, data_start, data_size);
                            break;
                        }
                        write(file_fd, buffer, valread);
                    }

                    close(file_fd);
                }
            }
        }
    }

    // Send response
    const char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nConnection: close\r\n\r\n<html><body>File uploaded successfully</body></html>";
    write(client_socket, response, strlen(response));
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

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

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            close(server_fd);
            exit(EXIT_FAILURE);
        }
        handle_client(new_socket);
        close(new_socket);
    }

    return 0;
}