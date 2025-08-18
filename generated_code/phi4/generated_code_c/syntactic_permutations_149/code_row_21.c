#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080

int insert_user_message_in_db(const char *username, const char *message) {
    // Placeholder for database insertion logic
    printf("Inserting into DB: Username=%s, Message=%s\n", username, message);
    return 1; // Assume success
}

void handle_request(int client_socket) {
    char buffer[1024] = {0};
    read(client_socket, buffer, sizeof(buffer));

    char *username_start = strstr(buffer, "username=");
    char *message_start = strstr(buffer, "message=");

    if (username_start && message_start) {
        username_start += 9; // Move past 'username='
        char *username_end = strchr(username_start, '&');
        if (!username_end) username_end = username_start + strlen(username_start);
        
        message_start += 8; // Move past 'message='
        char *message_end = strchr(message_start, ' ');
        if (!message_end) message_end = message_start + strlen(message_start);

        char username[256];
        strncpy(username, username_start, username_end - username_start);
        username[username_end - username_start] = '\0';

        char message[1024];
        strncpy(message, message_start, message_end - message_start);
        message[message_end - message_start] = '\0';

        insert_user_message_in_db(username, message);

        const char *redirect_html =
            "HTTP/1.1 302 Found\r\n"
            "Location: /messages\r\n"
            "\r\n";

        write(client_socket, redirect_html, strlen(redirect_html));
    }
}

void start_server() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

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

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            continue;
        }

        handle_request(new_socket);

        close(new_socket);
    }
}

int main() {
    start_server();
    return 0;
}