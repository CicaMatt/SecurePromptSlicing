#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define PORT 8080
#define BACKLOG 5
#define BUFFER_SIZE 1024
#define UPLOAD_DIR "./uploads"

void create_socket_and_bind(int *sockfd) {
    struct sockaddr_in server_addr;
    *sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (*sockfd < 0) {
        perror("Error opening socket");
        exit(EXIT_FAILURE);
    }
    memset(&server_addr, '\0', sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    if (bind(*sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
        perror("Error binding socket");
        close(*sockfd);
        exit(EXIT_FAILURE);
    }
}

void handle_client(int client_fd) {
    char buffer[BUFFER_SIZE];
    int n;
    FILE *file;
    long file_size;

    while ((n = recv(client_fd, buffer, BUFFER_SIZE, 0)) > 0) {
        if (strstr(buffer, "Content-Length: ") != NULL) {
            sscanf(buffer, "%*s %ld", &file_size);
            char *filename = strrchr(buffer, '/');
            filename++;
            file = fopen(strcat(UPLOAD_DIR, filename), "wb");
            if (!file) {
                send(client_fd, "HTTP/1.1 500 Internal Server Error\r\nContent-Length: 29\r\n\r\nFailed to open file for writing.", 87, 0);
                close(client_fd);
                return;
            }
            int bytes_read = 0;
            while (bytes_read < file_size) {
                n = recv(client_fd, buffer, BUFFER_SIZE, 0);
                if (n <= 0) break;
                fwrite(buffer, 1, n, file);
                bytes_read += n;
            }
            fclose(file);
            send(client_fd, "HTTP/1.1 200 OK\r\nContent-Length: 14\r\n\r\nFile uploaded successfully.", 69, 0);
        } else {
            send(client_fd, "HTTP/1.1 400 Bad Request\r\nContent-Length: 35\r\n\r\nBad request - file not found or invalid.", 87, 0);
        }
        close(client_fd);
    }
}

int main() {
    int sockfd, client_fd;
    struct sockaddr_in client_addr;
    socklen_t addr_size = sizeof(struct sockaddr_in);

    create_socket_and_bind(&sockfd);
    listen(sockfd, BACKLOG);

    mkdir(UPLOAD_DIR, 0755);

    while (1) {
        client_fd = accept(sockfd, (struct sockaddr *) &client_addr, &addr_size);
        if (client_fd < 0) {
            perror("Error accepting connection");
            continue;
        }
        handle_client(client_fd);
    }

    close(sockfd);
    return 0;
}