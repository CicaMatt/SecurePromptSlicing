#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 8080

typedef struct {
    char username[50];
    char message[256];
} Message;

int insert_user_message_in_db(const char *username, const char *message) {
    // Dummy database insertion logic
    printf("Inserting into DB: User=%s, Message=%s\n", username, message);
    return 1;  // Return success status
}

void display_messages() {
    // Dummy data for demonstration
    Message messages[] = {
        {"Alice", "Hello World!"},
        {"Bob", "Hi there!"},
        {"Charlie", "How are you?"}
    };
    
    int num_messages = sizeof(messages) / sizeof(messages[0]);
    printf("Messages:\n");
    for (int i = 0; i < num_messages; ++i) {
        printf("User: %s\nMessage: %s\n\n", messages[i].username, messages[i].message);
    }
}

void handle_post_request(int client_socket) {
    char buffer[1024] = {0};
    read(client_socket, buffer, 1024);

    // Extract username and message from the request
    char *username_start = strstr(buffer, "username=");
    char *message_start = strstr(buffer, "message=");
    
    if (!username_start || !message_start) {
        write(client_socket, "Invalid request\n", 17);
        return;
    }

    // Adjust pointers to get actual values
    username_start += strlen("username=");
    message_start += strlen("message=");

    char username[50];
    strncpy(username, username_start, strcspn(username_start, "&"));
    
    char message[256];
    strncpy(message, message_start, strcspn(message_start, "\r\n"));

    // Insert the message into the database
    if (insert_user_message_in_db(username, message)) {
        write(client_socket, "HTTP/1.1 302 Found\r\nLocation: /\r\n\r\n", 47);
    } else {
        write(client_socket, "Error inserting message\n", 23);
    }
}

void handle_get_request(int client_socket) {
    char response[] = 
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html; charset=UTF-8\r\n"
        "\r\n"
        "<html><body>";

    display_messages();

    response += strlen(response);
    strcat(response, "</body></html>");

    write(client_socket, response, strlen(response));
}

void start_server() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Set server address and port
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind the socket to the IP/port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Start listening for connections
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    printf("Server started on port %d\n", PORT);

    while ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))) {
        char buffer[1024] = {0};
        
        // Read the request
        read(new_socket, buffer, 1024);
        
        if (strstr(buffer, "POST /post") != NULL) {
            handle_post_request(new_socket);
        } else if (strstr(buffer, "GET /") != NULL) {
            handle_get_request(new_socket);
        } else {
            char *not_found_response = 
                "HTTP/1.1 404 Not Found\r\n"
                "Content-Type: text/plain; charset=UTF-8\r\n"
                "\r\n"
                "Not Found";
            
            write(new_socket, not_found_response, strlen(not_found_response));
        }

        close(new_socket);
    }

    if (new_socket < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }
}

int main() {
    start_server();
    return 0;
}