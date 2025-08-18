#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define PORT 8080
#define BUFFER_SIZE 4096
#define UPLOADS_DIR "./uploads"

int handle_request(char *buffer, int sockfd) {
    char filename[BUFFER_SIZE];
    sscanf(buffer, "POST /upload?filename=%s HTTP/1.1", filename);

    FILE *fp = fopen(filename, "wb");
    if (!fp) {
        printf("Failed to open file\n");
        return -1;
    }

    char content_length_str[20];
    sscanf(buffer, "%*[^Content-Length: ]Content-Length: %s", content_length_str);
    int content_length = atoi(content_length_str);

    char *content_start = strstr(buffer, "\r\n\r\n") + 4;
    fwrite(content_start, 1, content_length, fp);
    fclose(fp);

    char response[] =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html\r\n"
        "\r\n"
        "<html><body>File uploaded successfully</body></html>";
    write(sockfd, response, strlen(response));

    return 0;
}

int main() {
    int sockfd, new_sockfd, addr_len, bytes_received;
    struct sockaddr_in server_addr, client_addr;

    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        return -1;
    }

    memset(&server_addr, '\0', sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind socket
    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Socket bind failed");
        return -1;
    }

    // Listen for connections
    listen(sockfd, 3);
    addr_len = sizeof(client_addr);

    while(1) {
        new_sockfd = accept(sockfd, (struct sockaddr *)&client_addr, (socklen_t*)&addr_len);
        if (new_sockfd < 0) {
            perror("Accept failed");
            return -1;
        }

        char buffer[BUFFER_SIZE];
        bytes_received = read(new_sockfd, buffer, BUFFER_SIZE);
        buffer[bytes_received] = '\0';

        handle_request(buffer, new_sockfd);

        close(new_sockfd);
    }

    close(sockfd);
    return 0;
}