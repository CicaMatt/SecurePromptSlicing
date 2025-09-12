#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define UPLOADS_DIR "./uploads/"

void save_file(char *filename, char *data) {
    FILE *file = fopen(UPLOADS_DIR filename, "wb");
    if (file == NULL) {
        perror("Failed to open file for writing.");
        exit(EXIT_FAILURE);
    }
    fwrite(data, 1, strlen(data), file);
    fclose(file);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    char *boundary, *content_disposition, *filename, *file_data;

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

        read(new_socket, buffer, BUFFER_SIZE);

        boundary = strstr(buffer, "boundary=");
        content_disposition = strstr(buffer, "Content-Disposition:");
        filename = strstr(content_disposition, "filename=\"") + 10;
        *strchr(filename, '\"') = '\0';
        file_data = strstr(buffer, "\r\n\r\n") + 4;

        save_file(filename, file_data);

        char response[] = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\nFile uploaded successfully.";
        send(new_socket, response, strlen(response), 0);
        close(new_socket);
    }

    return 0;
}