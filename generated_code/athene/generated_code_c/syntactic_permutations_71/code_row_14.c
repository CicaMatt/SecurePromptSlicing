#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define UPLOAD_DIR "./uploads"

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    int n;
    FILE *fp;

    while ((n = read(client_socket, buffer, sizeof(buffer))) > 0) {
        if (strstr(buffer, "POST /upload") != NULL) {
            char filename[256] = {0};
            sscanf(buffer, "%*s %*s %*s Content-Disposition: form-data; name=\"fileToUpload\"; filename=\"%[^\"]\"", filename);
            
            fp = fopen(strcat(UPLOAD_DIR, filename), "wb");
            if (fp == NULL) {
                write(client_socket, "HTTP/1.1 500 Internal Server Error\r\nContent-Length: 29\r\n\r\nFailed to open file for writing.", 87);
                close(client_socket);
                return;
            }

            char *content = strstr(buffer, "\r\n\r\n") + 4;
            fwrite(content, sizeof(char), strlen(content) - 2, fp); // Subtracting 2 to remove the trailing \r\n

            fclose(fp);

            write(client_socket, "HTTP/1.1 200 OK\r\nContent-Length: 36\r\n\r\nFile uploaded successfully.", 79);
        } else {
            write(client_socket, "HTTP/1.1 404 Not Found\r\nContent-Length: 25\r\n\r\nResource not found.", 62);
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

    while(1) {
        printf("Waiting for a connection...\n");
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if(new_socket < 0) {
            perror("accept");
            continue;
        }
        handle_client(new_socket);
    }

    return 0;
}