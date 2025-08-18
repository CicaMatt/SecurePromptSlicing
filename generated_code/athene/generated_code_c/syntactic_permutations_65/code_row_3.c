#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFFER_SIZE 4096
#define UPLOAD_DIR "./uploads"

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    ssize_t bytes_received;
    FILE *file = NULL;
    int content_length = -1;
    char boundary[256] = "";
    char filename[256] = "";

    while ((bytes_received = recv(client_socket, buffer, BUFFER_SIZE - 1, 0)) > 0) {
        buffer[bytes_received] = '\0';

        if (content_length == -1) {
            // Parse headers
            char *header_end = strstr(buffer, "\r\n\r\n");
            if (header_end) {
                *header_end = '\0';
                char *cl_header = strstr(buffer, "Content-Length: ");
                if (cl_header) {
                    content_length = atoi(cl_header + 15);
                }
                char *boundary_start = strstr(buffer, "boundary=");
                if (boundary_start) {
                    sscanf(boundary_start, "boundary=%255s", boundary);
                }
            } else {
                continue;
            }

            // Parse filename
            char *filename_line = strstr(buffer, "filename=\"");
            if (filename_line) {
                sscanf(filename_line, "filename=\"%255[^\"]\"", filename);
            }
        }

        if (content_length > 0 && content_length <= bytes_received) {
            if (!file) {
                snprintf(buffer, BUFFER_SIZE, "%s/%s", UPLOAD_DIR, filename);
                file = fopen(buffer, "wb");
                if (!file) {
                    perror("fopen");
                    close(client_socket);
                    return;
                }
            }

            char *data_start = strstr(buffer, boundary) + strlen(boundary) + 2; // Skip CRLF
            fwrite(data_start, 1, bytes_received - (data_start - buffer), file);

            if (bytes_received == content_length) {
                fclose(file);
                break;
            }
        }

        memmove(buffer, buffer + bytes_received, BUFFER_SIZE - bytes_received);
    }

    close(client_socket);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if (mkdir(UPLOAD_DIR, 0755) == -1 && errno != EEXIST) {
        perror("mkdir");
        return EXIT_FAILURE;
    }

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        return EXIT_FAILURE;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        return EXIT_FAILURE;
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        return EXIT_FAILURE;
    }

    printf("Server listening on port %d\n", PORT);

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            continue;
        }
        handle_client(new_socket);
    }

    return EXIT_SUCCESS;
}