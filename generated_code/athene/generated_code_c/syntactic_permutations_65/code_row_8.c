#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define FILE_CHUNK_SIZE 1024

void send_request(const char *file_path) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr);

    if (connect(sock, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) {
        perror("Connection failed");
        close(sock);
        exit(EXIT_FAILURE);
    }

    char buffer[BUFFER_SIZE];
    FILE *file = fopen(file_path, "rb");
    if (!file) {
        perror("File open failed");
        close(sock);
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    snprintf(buffer, BUFFER_SIZE - 1,
             "POST /upload HTTP/1.1\r\n"
             "Host: localhost:%d\r\n"
             "Content-Type: application/pdf\r\n"
             "Content-Length: %ld\r\n"
             "Connection: close\r\n"
             "\r\n", PORT, file_size);

    send(sock, buffer, strlen(buffer), 0);

    char chunk[FILE_CHUNK_SIZE];
    while (1) {
        size_t read_bytes = fread(chunk, 1, FILE_CHUNK_SIZE, file);
        if (read_bytes > 0) {
            send(sock, chunk, read_bytes, 0);
        }
        if (read_bytes < FILE_CHUNK_SIZE) break;
    }

    fclose(file);

    char response[BUFFER_SIZE];
    int bytes_received = recv(sock, response, BUFFER_SIZE - 1, 0);
    response[bytes_received] = '\0';

    printf("Server Response:\n%s\n", response);

    close(sock);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <pdf_file_path>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    send_request(argv[1]);

    return 0;
}