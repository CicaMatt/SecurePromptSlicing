#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void send_http_request(const char *filename) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Connection failed");
        close(sock);
        exit(EXIT_FAILURE);
    }

    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("File open failed");
        close(sock);
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char boundary[] = "---------------------------boundary";
    char buffer[BUFFER_SIZE];
    snprintf(buffer, sizeof(buffer), 
             "POST /upload HTTP/1.1\r\n"
             "Host: localhost:%d\r\n"
             "Content-Type: multipart/form-data; boundary=%s\r\n"
             "Content-Length: %ld\r\n"
             "\r\n", PORT, boundary, file_size + strlen(boundary) * 3 + 200);

    send(sock, buffer, strlen(buffer), 0);

    snprintf(buffer, sizeof(buffer), "--%s\r\nContent-Disposition: form-data; name=\"file\"; filename=\"%s\"\r\n"
             "Content-Type: application/pdf\r\n\r\n", boundary, filename);
    send(sock, buffer, strlen(buffer), 0);

    size_t n;
    while ((n = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        send(sock, buffer, n, 0);
    }

    snprintf(buffer, sizeof(buffer), "\r\n--%s--\r\n", boundary);
    send(sock, buffer, strlen(buffer), 0);

    fclose(file);

    char response[BUFFER_SIZE];
    int bytes_received = recv(sock, response, BUFFER_SIZE - 1, 0);
    if (bytes_received > 0) {
        response[bytes_received] = '\0';
        printf("Server Response:\n%s\n", response);
    }

    close(sock);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <pdf_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    send_http_request(argv[1]);

    return EXIT_SUCCESS;
}