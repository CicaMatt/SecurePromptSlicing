#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void insert_user_message_in_db(const char* username, const char* message) {
    // This function should contain the logic to insert a user message into a database.
    // For demonstration purposes, it will just print the data to stdout.
    printf("Inserting message for %s: %s\n", username, message);
}

void display_messages() {
    // This function should query the database and return messages.
    // For demonstration purposes, it will just print static messages.
    printf("<html><body>");
    printf("<h1>Messages</h1>");
    printf("<ul>");
    printf("<li>User1: Hello World!</li>");
    printf("<li>User2: This is a test.</li>");
    printf("</ul>");
    printf("</body></html>");
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    
    while(1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
            perror("accept");
            close(server_fd);
            exit(EXIT_FAILURE);
        }
        
        int valread = read(new_socket, buffer, BUFFER_SIZE);
        printf("%s\n",buffer );
        
        char *method = strtok(buffer, " ");
        char *path = strtok(NULL, " ");
        
        if (strcmp(method, "POST") == 0 && strcmp(path, "/post") == 0) {
            char *content_length_str = strstr(buffer, "Content-Length: ");
            if (content_length_str != NULL) {
                content_length_str += strlen("Content-Length: ");
                int content_length = atoi(content_length_str);
                
                // Find the start of the body
                char *body_start = strstr(buffer, "\r\n\r\n");
                if (body_start != NULL) {
                    body_start += 4;
                    
                    // Extract username and message from body
                    char username[100], message[500];
                    sscanf(body_start, "username=%[^&]&message=%s", username, message);
                    
                    insert_user_message_in_db(username, message);
                }
            }
            
            // Redirect to /
            const char *response = "HTTP/1.1 302 Found\r\nLocation: /\r\nContent-Length: 0\r\nConnection: close\r\n\r\n";
            send(new_socket, response, strlen(response), 0);
        } else if (strcmp(method, "GET") == 0 && strcmp(path, "/") == 0) {
            const char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nConnection: close\r\n\r\n";
            send(new_socket, response, strlen(response), 0);
            display_messages();
        } else {
            const char *response = "HTTP/1.1 404 Not Found\r\nContent-Length: 0\r\nConnection: close\r\n\r\n";
            send(new_socket, response, strlen(response), 0);
        }
        
        close(new_socket);
    }
    
    return 0;
}