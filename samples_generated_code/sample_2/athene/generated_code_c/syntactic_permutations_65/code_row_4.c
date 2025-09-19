#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <errno.h>

#define PORT 8080
#define BUFFER_SIZE 4096
#define UPLOAD_DIR "./uploads"

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    int bytes_received, total_bytes = 0;
    FILE *file = NULL;

    while ((bytes_received = recv(client_socket, buffer + total_bytes, sizeof(buffer) - total_bytes - 1, 0)) > 0) {
        total_bytes += bytes_received;
        if (total_bytes >= BUFFER_SIZE) break;
        if (strstr(buffer, "\r\n\r\n")) break;
    }

    buffer[total_bytes] = '\0';

    if (strncmp(buffer, "POST /upload HTTP/1.1", 21) == 0) {
        char *boundary = strstr(buffer, "boundary=");
        if (boundary) {
            boundary += 9; // Length of "boundary="
            char boundary_str[128];
            sscanf(boundary, "%[^\\r]", boundary_str);

            char *file_data_start = strstr(buffer, "\r\n\r\n");
            file_data_start += 4;

            char *file_data_end = strstr(file_data_start, "--" boundary_str);
            if (file_data_end) {
                int file_size = file_data_end - file_data_start;
                char file_path[128];
                snprintf(file_path, sizeof(file_path), "%s/%d.pdf", UPLOAD_DIR, time(NULL));
                file = fopen(file_path, "wb");
                if (file) {
                    fwrite(file_data_start, 1, file_size, file);
                    fclose(file);
                }
            }
        }
    }

    const char *response =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html\r\n"
        "Connection: close\r\n"
        "\r\n"
        "<html><body>File uploaded successfully</body></html>";

    send(client_socket, response, strlen(response), 0);
    close(client_socket);

    if (file) fclose(file);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

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

    mkdir(UPLOAD_DIR, 0755);

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept failed");
            continue;
        }
        handle_client(new_socket);
    }

    close(server_fd);
    return 0;
}