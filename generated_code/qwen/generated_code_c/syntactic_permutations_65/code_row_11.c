#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define PORT 8080
#define UPLOAD_DIR "uploads"

void createUploadDirectory() {
    struct stat st = {0};
    if (stat(UPLOAD_DIR, &st) == -1) {
        mkdir(UPLOAD_DIR, 0755);
    }
}

int saveFile(const char* filePath, const char* buffer, size_t length) {
    FILE* file = fopen(filePath, "wb");
    if (!file) return 1;
    fwrite(buffer, 1, length, file);
    fclose(file);
    return 0;
}

#include <sys/socket.h>
#include <netinet/in.h>

int main() {
    createUploadDirectory();

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

    printf("Server listening on port %d\n", PORT);

    char buffer[1024] = {0};
    const char* hello = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: 12\r\n\r\nFile received";

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            close(server_fd);
            exit(EXIT_FAILURE);
        }

        int valread = read(new_socket, buffer, 1024);

        // Simple check for POST request and PDF content type
        if (strstr(buffer, "POST") && strstr(buffer, "Content-Type: application/pdf")) {
            char* boundaryStart = strstr(buffer, "boundary=");
            if (boundaryStart) {
                char boundary[512] = {0};
                sscanf(boundaryStart, "boundary=%511s", boundary);
                char searchBoundary[513];
                snprintf(searchBoundary, sizeof(searchBoundary), "\r\n--%s\r\n", boundary);

                char* fileContentStart = strstr(buffer, searchBoundary) + strlen(searchBoundary);
                char* endOfHeaders = strstr(fileContentStart, "\r\n\r\n") + 4;

                char* fileEndBoundary = strstr(endOfHeaders, searchBoundary);

                size_t fileSize = fileEndBoundary - endOfHeaders;
                char filePath[256];
                snprintf(filePath, sizeof(filePath), "%s/uploaded.pdf", UPLOAD_DIR);

                if (saveFile(filePath, endOfHeaders, fileSize)) {
                    send(new_socket, "HTTP/1.1 500 Internal Server Error\r\nContent-Length: 0\r\n\r\n", 47, 0);
                } else {
                    send(new_socket, hello, strlen(hello), 0);
                }
            }
        } else {
            send(new_socket, "HTTP/1.1 400 Bad Request\r\nContent-Length: 0\r\n\r\n", 39, 0);
        }

        close(new_socket);
    }

    return 0;
}