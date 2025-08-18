#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 8080

typedef struct {
    char username[50];
    char message[256];
} Message;

int insert_message_to_db(const char *username, const char *message) {
    // Simulated database insertion
    printf("Inserting into DB: %s - %s\n", username, message);
    return 1; // Success
}

void display_messages() {
    // Simulate fetching messages from a database and displaying them
    Message messages[] = {
        {"Alice", "Hello World!"},
        {"Bob", "Hi there!"}
    };
    
    printf("Messages:\n");
    for (int i = 0; i < sizeof(messages) / sizeof(messages[0]); ++i) {
        printf("%s: %s\n", messages[i].username, messages[i].message);
    }
}

void handle_post_request(int client_sock) {
    char buffer[1024] = {0};
    read(client_sock, buffer, 1023);

    Message msg;
    sscanf(buffer, "POST /post?username=%[^&]&message=%s", msg.username, msg.message);

    if (insert_message_to_db(msg.username, msg.message)) {
        const char *redirect_msg = "HTTP/1.1 303 See Other\r\nLocation: /\r\nContent-Length: 0\r\nConnection: close\r\n\r\n";
        send(client_sock, redirect_msg, strlen(redirect_msg), 0);
    }
}

void handle_get_request(int client_sock) {
    if (strstr(buffer, "GET / ")) {
        display_messages();
        
        const char *html_response = 
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/html; charset=UTF-8\r\n"
            "Connection: close\r\n\r\n"
            "<html><body>"
            "<h1>Messages</h1>";
            
        for (int i = 0; i < sizeof(messages) / sizeof(messages[0]); ++i) {
            char line[300];
            snprintf(line, sizeof(line), "<p>%s: %s</p>", messages[i].username, messages[i].message);
            html_response = strncat(html_response, line, sizeof(line));
        }
        
        html_response = strcat(html_response,
            "</body></html>");
            
        send(client_sock, html_response, strlen(html_response), 0);
    }
}

int main() {
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

    printf("Server listening on port %d\n", PORT);

    while ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))) {
        if (new_socket < 0) {
            perror("accept");
            close(new_socket);
            continue;
        }

        char buffer[1024] = {0};
        read(new_socket, buffer, 1023);

        if (strncmp(buffer, "POST /post", 10) == 0) {
            handle_post_request(new_socket);
        } else if (strncmp(buffer, "GET / ", 6) == 0) {
            handle_get_request(new_socket);
        }

        close(new_socket);
    }

    return 0;
}