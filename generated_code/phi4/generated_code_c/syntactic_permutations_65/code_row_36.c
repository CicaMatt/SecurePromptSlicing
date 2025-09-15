#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#define BUFFER_SIZE 8192

void upload_pdf(const char *pdf_path, const char *upload_url) {
    FILE *file = fopen(pdf_path, "rb");
    if (!file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    #ifdef _WIN32
    int sockfd;
    WSADATA wsaData;

    WSAStartup(MAKEWORD(2, 2), &wsaData);

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

    if ((sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) {
        printf("Socket creation failed with error: %ld\n", WSAGetLastError());
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        printf("Connection failed with error: %d\n", WSAGetLastError());
        closesocket(sockfd);
        WSACleanup();
        exit(EXIT_FAILURE);
    }
    #else
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    #endif

    char buffer[BUFFER_SIZE];
    size_t bytes_read;

    // Send file content
    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
        #ifdef _WIN32
        if (send(sockfd, buffer, bytes_read, 0) == SOCKET_ERROR) {
            printf("Send failed with error: %d\n", WSAGetLastError());
            closesocket(sockfd);
            WSACleanup();
            exit(EXIT_FAILURE);
        }
        #else
        if (write(sockfd, buffer, bytes_read) < 0) {
            perror("Write to socket failed");
            close(sockfd);
            exit(EXIT_FAILURE);
        }
        #endif
    }

    fclose(file);

    #ifdef _WIN32
    closesocket(sockfd);
    WSACleanup();
    #else
    close(sockfd);
    #endif

    printf("File uploaded successfully.\n");
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <pdf_path> <upload_url>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *pdf_path = argv[1];
    const char *upload_url = argv[2];

    upload_pdf(pdf_path, upload_url);

    return 0;
}
