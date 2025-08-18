#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    const char *welcome_message = "HTTP/1.1 200 OK\nContent-Type: text/html\n\n<form action=\"/upload\" method=\"post\" enctype=\"multipart/form-data\"><input type=\"file\" name=\"pdfFile\" accept=\"application/pdf\"><button type=\"submit\">Upload</button></form>";
    const char *success_message = "HTTP/1.1 200 OK\nContent-Type: text/plain\n\nFile uploaded successfully.";
    const char *error_message = "HTTP/1.1 400 Bad Request\nContent-Type: text/plain\n\nInvalid request.";

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind the socket to the port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Listen for connections
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    while(1) {
        // Accept an incoming connection
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
            perror("accept");
            close(server_fd);
            exit(EXIT_FAILURE);
        }

        int bytes_read = read(new_socket, buffer, BUFFER_SIZE - 1);

        // Check for POST request
        if (strncmp(buffer, "POST /upload", 12) == 0) {
            char *file_start = strstr(buffer, "\r\n\r\n") + 4;
            char *boundary_start = strstr(buffer, "boundary=");
            boundary_start += 9; // Move past 'boundary='
            char boundary[64] = {0};
            sscanf(boundary_start, "%[^'\r\n']", boundary);

            char file_name[] = "./uploads/uploaded.pdf";
            FILE *file = fopen(file_name, "wb");
            if (!file) {
                send(new_socket, error_message, strlen(error_message), 0);
                close(new_socket);
                continue;
            }

            // Extract and write the file content
            while (bytes_read > 0) {
                char *boundary_pos = strstr(file_start, boundary);
                fwrite(file_start, 1, boundary_pos - file_start, file);

                bytes_read -= (boundary_pos - file_start);
                if (bytes_read <= 0) break;

                // Read next chunk
                memmove(buffer, boundary_pos, bytes_read);
                bytes_read = read(new_socket, buffer + bytes_read, BUFFER_SIZE - bytes_read - 1) + bytes_read;
                file_start = buffer;
            }

            fclose(file);
            send(new_socket, success_message, strlen(success_message), 0);
        } else {
            send(new_socket, welcome_message, strlen(welcome_message), 0);
        }

        close(new_socket);
    }

    close(server_fd);
    return 0;
}