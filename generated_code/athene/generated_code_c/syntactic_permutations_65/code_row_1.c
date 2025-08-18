#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFFER_SIZE 4096
#define UPLOAD_DIR "uploads"

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    int n;
    FILE *fp;
    char filename[256] = "";

    while ((n = read(client_socket, buffer, sizeof(buffer))) > 0) {
        if (strstr(buffer, "Content-Disposition: form-data; name=\"file\"; filename=\"") != NULL) {
            sscanf(buffer, "%*[^filename\"]filename=\"%[^\"]\"", filename);
            snprintf(buffer, sizeof(buffer), "%s/%s", UPLOAD_DIR, filename);
            fp = fopen(buffer, "wb");
        } else if (strstr(buffer, "\r\n\r\n") && fp != NULL) {
            fwrite(buffer + 4, 1, n - 4, fp);
            int content_length = 0;
            char *cl_str = strstr(buffer, "Content-Length: ");
            if (cl_str != NULL) {
                cl_str += strlen("Content-Length: ");
                sscanf(cl_str, "%d", &content_length);
                while (content_length > n - 4) {
                    int bytes_read = read(client_socket, buffer, sizeof(buffer));
                    fwrite(buffer, 1, bytes_read, fp);
                    content_length -= bytes_read;
                }
            }
            fclose(fp);
            break;
        }
    }

    char response[] =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html; charset=UTF-8\r\n\r\n"
        "<html><body>File uploaded successfully.</body></html>";
    write(client_socket, response, strlen(response));
    close(client_socket);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if (mkdir(UPLOAD_DIR, 0755) == -1 && errno != EEXIST) {
        perror("Failed to create uploads directory");
        exit(EXIT_FAILURE);
    }

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d...\n", PORT);

    while (1) {
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (new_socket < 0) {
            perror("Accept failed");
            continue;
        }
        handle_client(new_socket);
    }

    close(server_fd);
    return 0;
}