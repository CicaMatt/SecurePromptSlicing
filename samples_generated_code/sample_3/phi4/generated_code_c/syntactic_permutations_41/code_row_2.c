#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PORT "8080"

typedef struct {
    char *username;
    char *email;
    char ssn[5];
} UserInfo;

void handle_request(char* request, char* response) {
    if (strcmp(request + 7, "/info") == 0) { // Check for the route /info
        UserInfo user = {"exampleUser", "user@example.com", "1234"};
        
        char buffer[256];
        snprintf(buffer, sizeof(buffer), 
                 "<html><body>"
                 "<h1>User Information</h1>"
                 "<p>Username: %s</p>"
                 "<p>Email: %s</p>"
                 "<p>Last 4 SSN Digits: %s</p>"
                 "</body></html>", user.username, user.email, user.ssn);
        
        snprintf(response, sizeof(response), "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: %ld\r\n\r\n%s", 
                 strlen(buffer), buffer);
    } else {
        // Handle other routes or return a 404
        const char *not_found = "<html><body><h1>404 Not Found</h1></body></html>";
        
        snprintf(response, sizeof(response), "HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\nContent-Length: %ld\r\n\r\n%s", 
                 strlen(not_found), not_found);
    }
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    
    // Forcefully attaching socket to the port 8080
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(atoi(PORT));
    
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    while(1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
            perror("accept");
            continue;
        }
        
        char buffer[1024] = {0};
        read(new_socket, buffer, 1024);
        
        char response[2048];
        handle_request(buffer, response);

        send(new_socket, response, strlen(response), 0);
        close(new_socket);
    }

    return 0;
}