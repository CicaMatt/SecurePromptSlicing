#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define SAVE_PATH "./uploads/"

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    int bytes_read;
    FILE *file;
    char file_name[256] = "";
    int content_length = 0;

    while ((bytes_read = recv(client_socket, buffer, BUFFER_SIZE - 1, 0)) > 0) {
        buffer[bytes_read] = '\0';
        if (strstr(buffer, "Content-Disposition") && strstr(buffer, "filename=")) {
            sscanf(buffer, "Content-Disposition: form-data; name=\"file\"; filename=\"%[^\"]\"", file_name);
            continue;
        }
        if (strstr(buffer, "Content-Length:")) {
            sscanf(buffer, "Content-Length: %d", &content_length);
            continue;
        }
        if (strstr(buffer, "\r\n\r\n")) {
            char *start_data = strstr(buffer, "\r\n\r\n") + 4;
            int data_len = bytes_read - (start_data - buffer);

            if (strlen(file_name) > 0) {
                file = fopen(strcat(SAVE_PATH, file_name), "wb");
                fwrite(start_data, 1, data_len, file);
                while ((bytes_read = recv(client_socket, buffer, BUFFER_SIZE, 0)) > 0) {
                    fwrite(buffer, 1, bytes_read, file);
                }
                fclose(file);
            }

            char response[] =
                "HTTP/1.1 200 OK\r\n"
                "Content-Type: text/html\r\n"
                "Connection: close\r\n\r\n"
                "<html><body>File uploaded successfully.</body></html>";
            send(client_socket, response, strlen(response), 0);
            break;
        }
    }

    close(client_socket);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    while (1) {
        printf("Listening on port %d...\n", PORT);
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (new_socket < 0) {
            perror("accept failed");
            continue;
        }
        handle_client(new_socket);
    }

    close(server_fd);
    return 0;
}