#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define UPLOADS_FOLDER "./uploads"

void create_directory() {
    if (mkdir(UPLOADS_FOLDER, 0755) == -1 && errno != EEXIST) {
        perror("Failed to create directory");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <path_to_pdf>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *file_path = argv[1];
    FILE *file = fopen(file_path, "rb");
    if (!file) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }

    struct sockaddr_in server_addr;
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Socket creation failed");
        fclose(file);
        return EXIT_FAILURE;
    }

    create_directory();

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0) {
        perror("Invalid address or address not supported");
        close(sock);
        fclose(file);
        return EXIT_FAILURE;
    }

    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        close(sock);
        fclose(file);
        return EXIT_FAILURE;
    }

    char file_name[256];
    strcpy(file_name, strrchr(file_path, '/') ? strrchr(file_path, '/') + 1 : file_path);

    char request[BUFFER_SIZE];
    snprintf(request, sizeof(request), "POST /upload HTTP/1.1\r\nHost: localhost:%d\r\nContent-Type: application/octet-stream\r\nContent-Disposition: form-data; name=\"file\"; filename=\"%s\"\r\n\r\n", PORT, file_name);

    if (send(sock, request, strlen(request), 0) < 0) {
        perror("Send failed");
        close(sock);
        fclose(file);
        return EXIT_FAILURE;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char buffer[BUFFER_SIZE];
    while (file_size > 0) {
        size_t bytes_to_send = file_size < BUFFER_SIZE ? file_size : BUFFER_SIZE;
        fread(buffer, 1, bytes_to_send, file);
        send(sock, buffer, bytes_to_send, 0);
        file_size -= bytes_to_send;
    }

    fclose(file);
    close(sock);

    return EXIT_SUCCESS;
}