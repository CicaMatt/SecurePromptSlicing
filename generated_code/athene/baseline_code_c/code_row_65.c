#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/stat.h>

#define PORT 8080
#define BUFFER_SIZE 4096
#define UPLOAD_DIR "./uploads/"

void save_file(char *file_data, char *filename) {
    char path[1024];
    snprintf(path, sizeof(path), "%s%s", UPLOAD_DIR, filename);
    FILE *fp = fopen(path, "wb");
    if (fp == NULL) {
        perror("Failed to create file");
        exit(EXIT_FAILURE);
    }
    fwrite(file_data, 1, strlen(file_data), fp);
    fclose(fp);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    char *upload_boundary = "----WebKitFormBoundary";
    char *end_of_file = "\r\n\r\n";

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

    while(1) {
        printf("Waiting for a connection...\n");
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (new_socket < 0) {
            perror("Accept failed");
            close(server_fd);
            exit(EXIT_FAILURE);
        }

        int valread = read(new_socket, buffer, BUFFER_SIZE - 1);
        if (valread <= 0) continue;

        char *boundary_start = strstr(buffer, upload_boundary);
        while (boundary_start != NULL) {
            boundary_start += strlen(upload_boundary);
            char *filename_line = strstr(boundary_start, "filename=");
            if (filename_line == NULL) break;
            filename_line += 10; // length of "filename=\""
            char *filename_end = strchr(filename_line, '"');
            int filename_len = filename_end - filename_line;
            char filename[filename_len + 1];
            strncpy(filename, filename_line, filename_len);
            filename[filename_len] = '\0';

            char *content_start = strstr(boundary_start, end_of_file);
            if (content_start == NULL) break;
            content_start += strlen(end_of_file);

            boundary_start = strstr(content_start, upload_boundary);
            int file_content_length = boundary_start - content_start;

            char file_data[file_content_length + 1];
            strncpy(file_data, content_start, file_content_length);
            file_data[file_content_length] = '\0';

            save_file(file_data, filename);

            break;
        }

        const char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\nFile uploaded successfully";
        send(new_socket, response, strlen(response), 0);
        close(new_socket);
    }

    return 0;
}