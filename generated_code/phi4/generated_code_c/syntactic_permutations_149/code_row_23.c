#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <winsock2.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif

#define PORT 8080
#define BUFFER_SIZE 1024

void insert_user_message_in_db(const char *username, const char *message) {
    // Simulate database insertion.
    printf("Inserting into DB: Username = %s, Message = %s\n", username, message);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};

#ifdef _WIN32
    WSADATA wsa_data;
    WSAStartup(MAKEWORD(2, 2), &wsa_data);
#endif

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
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
            perror("accept");
            continue;
        }

        memset(buffer, 0, BUFFER_SIZE);
        read(new_socket, buffer, BUFFER_SIZE);
        
        char *method = strtok(buffer, " ");
        if (strcmp(method, "POST") == 0) {
            char *path = strstr(buffer, " /post");
            if (path != NULL) {
                // Extract username and message
                const char *content_start = strstr(buffer, "\r\n\r\n") + 4;
                char content[BUFFER_SIZE] = {0};
                strncpy(content, content_start, BUFFER_SIZE - 1);
                
                char *username = strtok(content, "&");
                if (username != NULL) {
                    username = strchr(username, '=') + 1; // Move past '='
                    
                    char *message = strtok(NULL, "&");
                    if (message != NULL) {
                        message = strchr(message, '=') + 1; // Move past '='
                        
                        insert_user_message_in_db(username, message);
                        
                        char response[] =
                            "HTTP/1.1 302 Found\r\n"
                            "Location: /\r\n"
                            "\r\n";
                            
                        send(new_socket, response, strlen(response), 0);
                    }
                }
            }
        }

        close(new_socket);
    }

#ifdef _WIN32
    WSACleanup();
#endif

    return 0;
}