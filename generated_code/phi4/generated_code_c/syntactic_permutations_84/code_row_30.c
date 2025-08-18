#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5000

struct request {
    char method[10];
    char parameter[20];
    char value[100];
};

void handle_request(int client_sock) {
    char buffer[1024] = {0};
    read(client_sock, buffer, sizeof(buffer));

    struct request req;
    sscanf(buffer, "%s %s=%s", req.method, req.parameter, req.value);

    if (strcmp(req.parameter, "payload") != 0) {
        const char *error_msg = "Error: Missing 'payload' parameter.\n";
        write(client_sock, error_msg, strlen(error_msg));
    } else {
        if (strcmp(req.method, "Create") == 0) {
            const char *error_msg = "Error: 'Create' type not allowed.\n";
            write(client_sock, error_msg, strlen(error_msg));
        } else {
            // Handle other methods or payload parsing here
            const char *response_msg = "Payload received successfully.\n";
            write(client_sock, response_msg, strlen(response_msg));
        }
    }

    close(client_sock);
}

int main() {
    int server_fd, new_socket;
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
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Listening on port %d...\n", PORT);

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            continue;
        }
        
        handle_request(new_socket);
    }

    return 0;
}