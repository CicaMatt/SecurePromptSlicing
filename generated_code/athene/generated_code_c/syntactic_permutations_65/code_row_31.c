#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080
#define BUFFER_SIZE 4096
#define UPLOAD_DIR "./uploads"

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    int bytes_read;
    FILE *file = NULL;
    char file_name[256] = {0};
    char content_type[] = "Content-Type: application/pdf";
    int state = 0; // 0 - waiting for headers, 1 - reading filename, 2 - writing file

    while ((bytes_read = recv(client_socket, buffer, BUFFER_SIZE - 1, 0)) > 0) {
        buffer[bytes_read] = '\0';

        if (state == 0) {
            char *boundary = strstr(buffer, "boundary=");
            if (boundary != NULL) {
                boundary += strlen("boundary=");
                state = 1;
            }
        } else if (state == 1) {
            char *filename_start = strstr(buffer, "filename=\"");
            if (filename_start != NULL) {
                filename_start += strlen("filename=\"");
                char *filename_end = strchr(filename_start, '"');
                if (filename_end != NULL) {
                    int len = filename_end - filename_start;
                    strncpy(file_name, filename_start, len);
                    file_name[len] = '\0';
                    state = 2;
                }
            }
        } else if (state == 2) {
            char *content_type_pos = strstr(buffer, content_type);
            if (content_type_pos != NULL) {
                char *data_start = strstr(content_type_pos + strlen(content_type), "\r\n\r\n");
                if (data_start != NULL) {
                    data_start += 4; // Skip the \r\n\r\n
                    file = fopen(UPLOAD_DIR "/" file_name, "wb");
                    fwrite(data_start, 1, bytes_read - (data_start - buffer), file);
                }
            } else {
                if (file != NULL) {
                    fwrite(buffer, 1, bytes_read, file);
                }
            }
        }

        if (strchr(buffer, '\r') && strchr(buffer, '\n')) {
            break;
        }
    }

    if (file != NULL) {
        fclose(file);
    }

    char response[] = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nFile uploaded successfully.";
    send(client_socket, response, strlen(response), 0);
    close(client_socket);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    if (access(UPLOAD_DIR, F_OK) == -1) {
        mkdir(UPLOAD_DIR, 0755);
    }

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        close(server_fd);
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

    printf("Listening on port %d...\n", PORT);

    while (1) {
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (new_socket < 0) {
            perror("accept");
            continue;
        }
        handle_client(new_socket);
    }

    close(server_fd);
    return 0;
}