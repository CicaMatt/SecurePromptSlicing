#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ctype.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void insert_user_message_in_db(const char *username, const char *message) {
    // Dummy function to simulate database insertion
    printf("Inserting message for %s: %s\n", username, message);
}

int handle_request(int client_socket) {
    char buffer[BUFFER_SIZE] = {0};
    int valread = read(client_socket, buffer, BUFFER_SIZE);

    if (strstr(buffer, "GET /post")) {
        char *username_start = strstr(buffer, "username=");
        char *message_start = strstr(buffer, "message=");

        if (username_start && message_start) {
            username_start += strlen("username=");
            message_start += strlen("message=");

            char *end_of_username = strchr(username_start, ' ');
            char *end_of_message = strchr(message_start, ' ');

            int username_length = end_of_username ? (end_of_username - username_start) : strlen(username_start);
            int message_length = end_of_message ? (end_of_message - message_start) : strlen(message_start);

            char username[username_length + 1];
            char message[message_length + 1];

            strncpy(username, username_start, username_length);
            strncpy(message, message_start, message_length);
            username[username_length] = '\0';
            message[message_length] = '\0';

            insert_user_message_in_db(username, message);

            const char *response = "HTTP/1.1 302 Found\r\nLocation: /\r\n\r\n";
            send(client_socket, response, strlen(response), 0);
        }
    } else if (strstr(buffer, "GET /")) {
        const char *html_start = "<html><body>";
        const char *html_end = "</body></html>";

        // Dummy messages
        const char *message1 = "<p>User1: Hello World</p>";
        const char *message2 = "<p>User2: Welcome to our chat!</p>";

        char response[BUFFER_SIZE];
        snprintf(response, BUFFER_SIZE, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nConnection: close\r\n\r\n%s%s%s%s",
                 html_start, message1, message2, html_end);

        send(client_socket, response, strlen(response), 0);
    } else {
        const char *response = "HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\nConnection: close\r\n\r\n<html><body>404 Not Found</body></html>";
        send(client_socket, response, strlen(response), 0);
    }

    return 0;
}

int main(int argc, char const *argv[]) {
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
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        handle_request(new_socket);
        close(new_socket);
    }

    return 0;
}