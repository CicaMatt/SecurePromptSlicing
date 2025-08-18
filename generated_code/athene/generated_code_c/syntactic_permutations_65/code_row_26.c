#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <errno.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void save_file(char *filename, char *data) {
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) {
        perror("Failed to open file for writing");
        return;
    }
    fwrite(data, 1, strlen(data), fp);
    fclose(fp);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    char *upload_dir = "./uploads/";
    char *boundary = "----WebKitFormBoundary";

    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        return -1;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind the socket
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        return -1;
    }

    // Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        return -1;
    }

    printf("Server listening on port %d\n", PORT);

    while(1) {
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (new_socket < 0) {
            perror("Accept failed");
            continue;
        }

        int valread = read(new_socket, buffer, BUFFER_SIZE - 1);
        if (valread <= 0) {
            close(new_socket);
            continue;
        }

        char *start_content = strstr(buffer, "Content-Disposition: form-data; name=\"file\"; filename=");
        if (!start_content) {
            close(new_socket);
            continue;
        }

        start_content += strlen("Content-Disposition: form-data; name=\"file\"; filename=\"");
        char *end_filename = strchr(start_content, '"');
        int filename_len = end_filename - start_content;
        char filename[filename_len + 1];
        strncpy(filename, start_content, filename_len);
        filename[filename_len] = '\0';

        char full_path[256];
        snprintf(full_path, sizeof(full_path), "%s%s", upload_dir, filename);

        char *start_data = strstr(buffer, "\r\n\r\n");
        if (start_data) {
            start_data += 4; // Skip the \r\n\r\n
            char *end_data = strstr(start_data, boundary);
            int data_len = end_data - start_data;
            save_file(full_path, start_data);
        }

        const char *response = "HTTP/1.1 200 OK\r\nContent-Length: 0\r\nConnection: close\r\n\r\n";
        send(new_socket, response, strlen(response), 0);
        close(new_socket);
    }

    return 0;
}