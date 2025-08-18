#include <stdio.h>
#include <string.h>

#define PORT 8080

void handle_request(const char *path, const char *user_info) {
    if (strcmp(path, "/info") == 0) {
        printf("HTTP/1.1 200 OK\r\n");
        printf("Content-Type: text/html; charset=UTF-8\r\n");
        printf("\r\n");
        printf("<html><body>");
        printf("<h1>User Information</h1>");
        
        // Assuming user_info is a string in the format "username,email,SSN"
        char *token;
        char username[50], email[100], ssn[15];
        
        token = strtok((char *)user_info, ",");
        if (token != NULL) {
            strncpy(username, token, sizeof(username));
        }
        
        token = strtok(NULL, ",");
        if (token != NULL) {
            strncpy(email, token, sizeof(email));
        }
        
        token = strtok(NULL, ",");
        if (token != NULL) {
            snprintf(ssn, sizeof(ssn), "XXX-XX-%s", &token[strlen(token)-4]);
        }
        
        printf("<p>Username: %s</p>", username);
        printf("<p>Email: %s</p>", email);
        printf("<p>Last 4 Digits of SSN: %s</p>", ssn);
        
        printf("</body></html>");
    } else {
        printf("HTTP/1.1 404 Not Found\r\n");
        printf("Content-Type: text/html; charset=UTF-8\r\n");
        printf("\r\n");
        printf("<html><body><h1>404 Not Found</h1></body></html>");
    }
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        return -1;
    }
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    
    // Bind the socket to the port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        return -1;
    }
    
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        return -1;
    }
    
    printf("Listening on port %d...\n", PORT);
    
    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            continue;
        }
        
        char buffer[1024] = {0};
        int valread = read(new_socket, buffer, sizeof(buffer));
        
        char *method = strtok(buffer, " ");
        char *path = strtok(NULL, " ");
        
        // Example user information
        const char *user_info = "johndoe,john@example.com,123-45-6789";
        
        handle_request(path, user_info);
        
        send(new_socket, buffer, strlen(buffer), 0);
        close(new_socket);
    }
    
    return 0;
}