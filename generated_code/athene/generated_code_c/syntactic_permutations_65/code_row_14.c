#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <errno.h>

#define PORT 8080
#define BUFFER_SIZE 4096
#define UPLOAD_DIR "uploads"

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    int bytes_received, file_size;
    FILE *fp;

    // Read the HTTP request
    while ((bytes_received = recv(client_socket, buffer, sizeof(buffer), 0)) > 0) {
        if (strstr(buffer, "Content-Length:")) {
            sscanf(buffer, "%*s %d", &file_size);
            break;
        }
    }

    char file_name[256];
    memset(file_name, 0, sizeof(file_name));
    sscanf(buffer, "%*[^filename=]\"%[^\"]\"", file_name);

    // Create uploads directory if it doesn't exist
    mkdir(UPLOAD_DIR, 0777);

    char file_path[1024];
    snprintf(file_path, sizeof(file_path), "%s/%s", UPLOAD_DIR, file_name);
    fp = fopen(file_path, "wb");

    int bytes_written = 0;
    while (bytes_written < file_size) {
        if ((bytes_received = recv(client_socket, buffer, sizeof(buffer), 0)) <= 0) break;
        fwrite(buffer, 1, bytes_received, fp);
        bytes_written += bytes_received;
    }

    fclose(fp);

    const char *response =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/plain\r\n"
        "\r\n"
        "File uploaded successfully.\n";
    send(client_socket, response, strlen(response), 0);
    close(client_socket);
}

int main() {
    int server_fd, client_fd;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

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
        perror("listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    while (1) {
        if ((client_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept failed");
            continue;
        }
        handle_client(client_fd);
    }

    close(server_fd);
    return 0;
}