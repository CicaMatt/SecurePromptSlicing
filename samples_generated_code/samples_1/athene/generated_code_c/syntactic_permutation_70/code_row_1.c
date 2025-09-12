#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 4096
#define UPLOADS_DIR "uploads"

void create_directory(const char *dir) {
    struct stat st = {0};
    if (stat(dir, &st) == -1) {
        mkdir(dir, 0755);
    }
}

int handle_request(int client_socket) {
    char buffer[BUFFER_SIZE];
    ssize_t bytes_received;
    FILE *fp;

    while ((bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0)) > 0) {
        if (strstr(buffer, "POST /upload") != NULL) {
            const char *boundary = "-----------------------------";
            char filename[BUFFER_SIZE] = "";
            int content_disposition = 0;
            int file_data = 0;

            for (char *line = buffer; bytes_received > 0; line += strlen(line) + 1, bytes_received -= strlen(line) + 1) {
                if (content_disposition == 0 && strstr(line, "Content-Disposition") != NULL) {
                    content_disposition = 1;
                    sscanf(line, "Content-Disposition: form-data; name=\"file\"; filename=\"%[^\"]\"", filename);
                } else if (content_disposition == 1 && file_data == 0 && strstr(line, "Content-Type") != NULL) {
                    file_data = 1;
                } else if (content_disposition == 1 && file_data == 1 && strlen(line) == 0) {
                    fp = fopen(strcat(UPLOADS_DIR "/", filename), "wb");
                    if (fp == NULL) {
                        return -1;
                    }
                } else if (file_data == 1) {
                    fwrite(line, 1, strlen(line), fp);
                    if (strstr(line, boundary) != NULL) {
                        fclose(fp);
                        break;
                    }
                }
            }
        }
    }

    const char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\nFile uploaded successfully.";
    send(client_socket, response, strlen(response), 0);

    close(client_socket);
    return 0;
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    create_directory(UPLOADS_DIR);

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

    while (1) {
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (new_socket < 0) {
            perror("accept");
            continue;
        }
        handle_request(new_socket);
    }

    close(server_fd);
    return 0;
}