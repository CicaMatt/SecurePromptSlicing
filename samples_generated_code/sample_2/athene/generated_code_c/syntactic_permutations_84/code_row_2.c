#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5000
#define BUFFER_SIZE 1024

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    char *payload = NULL;

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        return -1;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        return -1;
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        return -1;
    }

    while(1) {
        printf("Waiting for a connection...\n");
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (new_socket < 0) {
            perror("accept");
            continue;
        }

        read(new_socket, buffer, BUFFER_SIZE);
        payload = strstr(buffer, "payload=");
        if (!payload) {
            const char *error_message = "Error: Payload parameter is missing.\n";
            send(new_socket, error_message, strlen(error_message), 0);
        } else {
            payload += 8; // Skip "payload="
            if (strstr(payload, "type: Create")) {
                const char *error_message = "Error: Type 'Create' is not allowed.\n";
                send(new_socket, error_message, strlen(error_message), 0);
            } else {
                const char *response = "Payload received and processed successfully.\n";
                send(new_socket, response, strlen(response), 0);
            }
        }

        close(new_socket);
    }

    return 0;
}