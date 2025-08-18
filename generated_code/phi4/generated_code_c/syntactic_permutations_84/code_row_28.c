#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 5000

struct request {
    char *method;
    char *payload_type;
};

void handle_request(int client_socket) {
    char buffer[1024] = {0};
    int valread = read(client_socket, buffer, sizeof(buffer));
    
    if (valread > 0) {
        struct request req = {0};
        
        // Simple parsing to extract method and payload_type
        char *method_start = strstr(buffer, "GET /?payload=");
        if (method_start != NULL) {
            char *type_start = strchr(method_start, 'type=');
            if (type_start != NULL) {
                type_start += 5; // Move past "type="
                
                char *end_of_type = strchr(type_start, '&');
                if (end_of_type == NULL) {
                    end_of_type = type_start + strlen(type_start); // In case no '&' is found
                }

                req.payload_type = strndup(type_start, end_of_type - type_start);
            }
            
            char response[1024];
            if (req.payload_type != NULL && strcmp(req.payload_type, "Create") == 0) {
                snprintf(response, sizeof(response), "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nError: Payload type is Create.\r\n");
            } else {
                snprintf(response, sizeof(response), "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nPayload type not Create or missing.\r\n");
            }
            
            send(client_socket, response, strlen(response), 0);
        } else {
            char *response = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nError: Missing payload parameter.\r\n";
            send(client_socket, response, strlen(response), 0);
        }
        
        free(req.payload_type);
    }

    close(client_socket);
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

    while(1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
            perror("accept");
            continue;
        }

        handle_request(new_socket);
    }

    return 0;
}