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
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Connection failed");
        close(sock);
        exit(EXIT_FAILURE);
    }

    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("File opening failed");
        close(sock);
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char boundary[16];
    snprintf(boundary, sizeof(boundary), "----------------%ld", (long)time(NULL));

    char header[BUFFER_SIZE];
    snprintf(header, sizeof(header),
             "POST /upload HTTP/1.1\r\n"
             "Host: localhost:%d\r\n"
             "Content-Type: multipart/form-data; boundary=%s\r\n"
             "Content-Length: %ld\r\n"
             "\r\n",
             PORT, boundary, file_size + strlen(boundary) * 3 + strlen(filename) + 100);

    send(sock, header, strlen(header), 0);

    char part1[BUFFER_SIZE];
    snprintf(part1, sizeof(part1),
             "--%s\r\n"
             "Content-Disposition: form-data; name=\"file\"; filename=\"%s\"\r\n"
             "Content-Type: application/pdf\r\n"
             "\r\n",
             boundary, filename);
    send(sock, part1, strlen(part1), 0);

    char buffer[BUFFER_SIZE];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        send(sock, buffer, bytes_read, 0);
    }

    const char *part2 =
        "\r\n"
        "--%s--\r\n";
    snprintf(part1, sizeof(part1), part2, boundary);
    send(sock, part1, strlen(part1), 0);

    fclose(file);
    close(sock);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <pdf_file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    send_http_request(argv[1]);

    return 0;
}