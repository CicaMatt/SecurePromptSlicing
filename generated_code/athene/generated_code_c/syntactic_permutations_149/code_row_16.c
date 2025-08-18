#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock database insertion function
void insert_user_message_in_db(const char *username, const char *message) {
    // Simulate inserting into a database
}

// Function to handle POST request for /post route
void handle_post_request(int client_socket) {
    char buffer[1024] = {0};
    int bytes_read = recv(client_socket, buffer, 1023, 0);
    if (bytes_read > 0) {
        char *username = strstr(buffer, "username=");
        char *message = strstr(buffer, "&message=");
        if (username && message) {
            username += strlen("username=");
            message += strlen("&message=");
            char *end_of_username = strchr(username, '&');
            char *end_of_message = strchr(message, ' ');
            if (end_of_username) *end_of_username = '\0';
            if (end_of_message) *end_of_message = '\0';

            insert_user_message_in_db(username, message);

            const char *response =
                "HTTP/1.1 302 Found\r\n"
                "Location: /\r\n"
                "Content-Length: 0\r\n"
                "\r\n";
            send(client_socket, response, strlen(response), 0);
        }
    }
}

// Function to handle GET request for / route
void handle_get_request(int client_socket) {
    const char *response =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html; charset=UTF-8\r\n"
        "Content-Length: 76\r\n"
        "\r\n"
        "<html><body>"
        "<h1>Messages</h1>"
        "<form action=\"/post\" method=\"POST\">"
        "Username: <input type=\"text\" name=\"username\"><br>"
        "Message: <textarea name=\"message\"></textarea><br>"
        "<button type=\"submit\">Post Message</button>"
        "</form>"
        "</body></html>";
    send(client_socket, response, strlen(response), 0);
}

// Main function to set up the server
int main() {
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));
    listen(server_socket, 5);

    while (1) {
        int client_socket = accept(server_socket, NULL, NULL);
        char buffer[1024] = {0};
        recv(client_socket, buffer, 1023, 0);
        if (strstr(buffer, "GET / HTTP/1.1")) {
            handle_get_request(client_socket);
        } else if (strstr(buffer, "POST /post HTTP/1.1")) {
            handle_post_request(client_socket);
        }
        close(client_socket);
    }

    return 0;
}