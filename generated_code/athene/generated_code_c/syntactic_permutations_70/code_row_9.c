#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <netinet/in.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define UPLOAD_DIR "./uploads"

void create_directory(const char *dir) {
    struct stat st = {0};
    if (stat(dir, &st) == -1) {
        mkdir(dir, 0700);
    }
}

int handle_request(int sockfd) {
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;
    FILE *fp;

    create_directory(UPLOAD_DIR);

    // Read the HTTP request
    while ((bytes_read = read(sockfd, buffer, BUFFER_SIZE - 1)) > 0) {
        buffer[bytes_read] = '\0';
        
        if (strstr(buffer, "Content-Disposition: form-data; name=\"file\"; filename=")) {
            const char *start_filename = strstr(buffer, "filename=\"") + strlen("filename=\"");
            const char *end_filename = strchr(start_filename, '\"');
            int filename_len = end_filename - start_filename;
            char filename[filename_len + 1];
            strncpy(filename, start_filename, filename_len);
            filename[filename_len] = '\0';

            // Open file for writing
            char filepath[256];
            snprintf(filepath, sizeof(filepath), "%s/%s", UPLOAD_DIR, filename);
            fp = fopen(filepath, "wb");
            if (fp == NULL) {
                return -1;
            }

            // Skip to the start of the file data
            const char *start_data = strstr(buffer, "\r\n\r\n") + 4;
            fwrite(start_data, 1, bytes_read - (start_data - buffer), fp);
            break;
        }
    }

    // Continue reading the file data if it spans multiple packets
    while ((bytes_read = read(sockfd, buffer, BUFFER_SIZE)) > 0) {
        fwrite(buffer, 1, bytes_read, fp);
    }

    fclose(fp);

    // Send HTTP response
    const char *response =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html\r\n"
        "\r\n"
        "<html><body>File uploaded successfully.</body></html>\r\n";
    write(sockfd, response, strlen(response));

    return 0;
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    while(1) {
        printf("Waiting for a connection...\n");
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        handle_request(new_socket);
        close(new_socket);
    }

    return 0;
}