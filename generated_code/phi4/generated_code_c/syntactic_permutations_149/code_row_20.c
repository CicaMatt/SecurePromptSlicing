#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080

void insert_user_message_in_db(const char *name, const char *message) {
    // Mock function to simulate database insertion
    printf("Inserting into DB: %s says %s\n", name, message);
}

char* get_request_line(int client_socket) {
    char buffer[1024] = {0};
    read(client_socket, buffer, sizeof(buffer));
    char *line = strtok(buffer, "\r\n");
    return line;
}

void handle_post_request(int client_socket) {
    char header[1024];
    snprintf(header, sizeof(header), "HTTP/1.1 302 Found\r\nLocation: /\r\nContent-Length: 0\r\nConnection: close\r\n\r\n");

    const char *name = getenv("NAME");
    const char *message = getenv("MESSAGE");

    if (name && message) {
        insert_user_message_in_db(name, message);
    }

    write(client_socket, header, strlen(header));
}

void handle_get_request(int client_socket) {
    char response[] =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html\r\n"
        "\r\n"
        "<html><body>"
        "<h1>Messages</h1>"
        "<ul>"
        // Mocked messages
        "<li>Alice says Hello World!</li>"
        "<li>Bob says C programming is awesome!</li>"
        "</ul>"
        "<form action=\"/post\" method=\"POST\">"
        "Name: <input type=\"text\" name=\"name\"><br>"
        "Message: <input type=\"text\" name=\"message\"><br>"
        "<input type=\"submit\" value=\"Submit\">"
        "</form>"
        "</body></html>";

    write(client_socket, response, strlen(response));
}

void handle_request(int client_socket) {
    char *request_line = get_request_line(client_socket);
    
    if (strncmp(request_line, "POST /post", 10) == 0) {
        handle_post_request(client_socket);
    } else if (strncmp(request_line, "GET /", 5) == 0) {
        handle_get_request(client_socket);
    }
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
    
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
            continue;
        }
        
        handle_request(new_socket);

        close(new_socket);
    }

    return 0;
}