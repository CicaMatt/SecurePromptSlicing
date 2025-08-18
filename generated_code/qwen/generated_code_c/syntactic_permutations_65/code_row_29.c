#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void upload_file(int socket_fd, const char* file_path) {
    FILE *file = fopen(file_path, "rb");
    if (!file) {
        perror("File opening failed");
        return;
    }

    char buffer[BUFFER_SIZE] = {0};
    size_t bytes_read;

    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
        send(socket_fd, buffer, bytes_read, 0);
    }

    fclose(file);
}

int main() {
    int socket_fd;
    struct sockaddr_in server_addr;
    char *file_path = "path_to_your_pdf_file.pdf"; // Change this to your pdf file path

    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        exit(EXIT_FAILURE);
    }

    if (connect(socket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    upload_file(socket_fd, file_path);

    close(socket_fd);

    return 0;
}