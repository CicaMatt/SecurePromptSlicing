#include <stdio.h>
#include <string.h>

#define USERNAME "user123"
#define EMAIL "user@example.com"
#define SSN "123-45-6789"

void handle_info_request() {
    printf("Content-Type: text/plain\n");
    printf("\n");
    printf("Username: %s\n", USERNAME);
    printf("Email: %s\n", EMAIL);
    printf("SSN: %s\n", SSN);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        return 1;
    }

    int port = atoi(argv[1]);

    // Simple HTTP server setup using a basic socket and listen mechanism
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        return -1;
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                   &opt, sizeof(opt))) {
        perror("setsockopt");
        return -1;
    }
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        return -1;
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        return -1;
    }

    while (1) {
        printf("Waiting for connections...\n");

        if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                                 (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            return -1;
        }

        read(new_socket, buffer, 1024);
        printf("Request: %s\n", buffer);

        // Check if the request is for /info
        if (strstr(buffer, "GET /info HTTP/1.1")) {
            handle_info_request();
        } else {
            printf("HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\n");
            printf("Not found\r\n");
        }

        close(new_socket);
    }
    
    return 0;
}
