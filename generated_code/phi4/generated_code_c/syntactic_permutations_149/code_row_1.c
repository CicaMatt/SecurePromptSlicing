#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 8080

void insert_user_message_in_db(const char *username, const char *message) {
    // Placeholder for database insertion logic
    printf("Inserting into DB: %s - %s\n", username, message);
}

const char* get_request_path(char *request) {
    char *path_start = strstr(request, "GET /") + 5;
    char *path_end = strchr(path_start, ' ');
    if (path_end == NULL) return "/";
    size_t path_len = path_end - path_start;
    char *path = malloc(path_len + 1);
    strncpy(path, path_start, path_len);
    path[path_len] = '\0';
    return path;
}

void handle_get_request(int client_socket) {
    const char *response =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html\r\n"
        "\r\n"
        "<html><body>"
        "<form action='/post' method='POST'>"
        "Username: <input type='text' name='username'><br>"
        "Message: <textarea name='message'></textarea><br>"
        "<input type='submit' value='Submit'>"
        "</form>"
        "</body></html>";
    send(client_socket, response, strlen(response), 0);
}

void handle_post_request(int client_socket) {
    char buffer[1024] = {0};
    read(client_socket, buffer, 1023);

    char *username_start = strstr(buffer, "username=");
    if (username_start == NULL) return;
    username_start += 9;

    char *message_start = strstr(username_start, "&message=");
    if (message_start == NULL) {
        message_start = strchr(username_start, '\r');
    } else {
        message_start += 9;
    }

    char *username_end = message_start ? message_start : strchr(username_start, '\r');
    size_t username_len = username_end - username_start;

    char *message_end = strchr(message_start, '\r');
    size_t message_len = message_end - message_start;

    char *username = malloc(username_len + 1);
    strncpy(username, username_start, username_len);
    username[username_len] = '\0';

    char *message = malloc(message_len + 1);
    strncpy(message, message_start, message_len);
    message[message_len] = '\0';

    insert_user_message_in_db(username, message);

    free(username);
    free(message);

    const char *redirect_response =
        "HTTP/1.1 302 Found\r\n"
        "Location: /\r\n"
        "\r\n";
    send(client_socket, redirect_response, strlen(redirect_response), 0);
}

void handle_request(int client_socket) {
    char buffer[1024] = {0};
    read(client_socket, buffer, 1023);

    if (strncmp(buffer, "GET ", 4) == 0) {
        handle_get_request(client_socket);
    } else if (strncmp(buffer, "POST ", 5) == 0) {
        handle_post_request(client_socket);
    }
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
        perror("listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept failed");
            continue;
        }

        handle_request(new_socket);

        close(new_socket);
    }

    return 0;
}