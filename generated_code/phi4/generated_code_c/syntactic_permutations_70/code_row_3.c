#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define BUFFER_SIZE 4096

void handle_request(int client_fd);
int upload_file(const char *file_name, const unsigned char *buffer, size_t buffer_size);

int main() {
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr;
    
    if (server_socket < 0) {
        perror("socket");
        return EXIT_FAILURE;
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        return EXIT_FAILURE;
    }

    if (listen(server_socket, 10) < 0) {
        perror("listen");
        return EXIT_FAILURE;
    }

    printf("Server is listening on port 8080...\n");

    while (1) {
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        int client_fd = accept(server_socket, (struct sockaddr *)&client_addr, &client_len);

        if (client_fd < 0) {
            perror("accept");
            continue;
        }

        handle_request(client_fd);
        close(client_fd);
    }

    return EXIT_SUCCESS;
}

void handle_request(int client_fd) {
    char buffer[BUFFER_SIZE];
    int bytes_read;

    while ((bytes_read = read(client_fd, buffer, BUFFER_SIZE - 1)) > 0) {
        buffer[bytes_read] = '\0';

        if (strstr(buffer, "POST /upload HTTP/1.1") != NULL) {
            char file_name[256];
            unsigned char file_content[BUFFER_SIZE];
            
            sscanf(buffer, "Content-Disposition: form-data; name=\"file\"; filename=\"%255[^"]\"", file_name);
            int content_start = strstr(buffer, "\r\n\r\n") - buffer + 4;
            bytes_read = read(client_fd, (char *)file_content, BUFFER_SIZE - 1);
            file_content[bytes_read] = '\0';

            if (upload_file(file_name, file_content, bytes_read) == 0) {
                write(client_fd, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nConnection: close\r\n\r\nFile uploaded successfully.\r\n", 87);
            } else {
                write(client_fd, "HTTP/1.1 500 Internal Server Error\r\nContent-Type: text/plain\r\nConnection: close\r\n\r\nFailed to upload file.\r\n", 102);
            }
        }

        break;
    }
}

int upload_file(const char *file_name, const unsigned char *buffer, size_t buffer_size) {
    FILE *fp = fopen("uploads/" file_name, "wb");
    
    if (!fp) {
        perror("fopen");
        return -1;
    }

    fwrite(buffer, 1, buffer_size, fp);
    fclose(fp);

    struct stat st;
    if (stat("uploads", &st) == -1 || !(st.st_mode & S_IFDIR)) {
        mkdir("uploads", 0755);
    }

    return 0;
}


To compile this code:

gcc -o simple_web_server simple_web_server.c
./simple_web_server