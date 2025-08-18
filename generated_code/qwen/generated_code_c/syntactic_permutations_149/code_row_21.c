#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080

void insert_user_message_in_db(const char *username, const char *message) {
    // Dummy function to simulate database insertion
    printf("Inserting into DB: User=%s, Message=%s\n", username, message);
}

void handle_request(int client_socket) {
    char buffer[1024] = {0};
    int valread = read(client_socket, buffer, 1024);

    if (strstr(buffer, "/post")) {
        const char *username_start = strstr(buffer, "username=") + strlen("username=");
        const char *username_end = strchr(username_start, '&');
        size_t username_len = username_end - username_start;
        char username[100];
        strncpy(username, username_start, username_len);
        username[username_len] = '\0';

        const char *message_start = strstr(buffer, "message=") + strlen("message=");
        const char *message_end = strchr(message_start, ' ');
        size_t message_len = message_end - message_start;
        char message[100];
        strncpy(message, message_start, message_len);
        message[message_len] = '\0';

        insert_user_message_in_db(username, message);

        const char *response = "HTTP/1.1 302 Found\r\nLocation: /messages\r\nContent-Length: 0\r\nConnection: close\r\n\r\n";
        send(client_socket, response, strlen(response), 0);
    } else {
        const char *response = "HTTP/1.1 404 Not Found\r\nContent-Length: 0\r\nConnection: close\r\n\r\n";
        send(client_socket, response, strlen(response), 0);
    }
}

int main(int argc, char const *argv[]) {
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

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            close(server_fd);
            exit(EXIT_FAILURE);
        }
        handle_request(new_socket);
        close(new_socket);
    }

    return 0;
}