#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define PORT 8080

void handle_request(int client_socket) {
    char buffer[1024] = {0};
    read(client_socket, buffer, sizeof(buffer));

    char *method = strtok(buffer, " ");
    char *path = strtok(NULL, " ");
    char *http_version = strtok(NULL, "\r\n");

    if (strcasecmp(method, "POST") == 0) {
        size_t content_length;
        const char *header_content_length = strstr(buffer, "Content-Length: ");
        
        if (header_content_length != NULL) {
            sscanf(header_content_length, "Content-Length: %zu", &content_length);
            
            char *body_start = strstr(buffer, "\r\n\r\n") + 4; // Find body start after headers
            if (strlen(body_start) < content_length)
                read(client_socket, buffer + strlen(buffer), content_length - strlen(body_start));
            
            char *name_field = strstr(body_start, "name=");
            if (name_field != NULL) {
                name_field += 5; // Move to the start of the actual name value
                const char *end_of_name = strchr(name_field, '&');
                if (!end_of_name)
                    end_of_name = body_start + content_length;
                
                size_t name_len = end_of_name - name_field;
                char response[1024];
                snprintf(response, sizeof(response), "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n%s", 
                         name_field);
                send(client_socket, response, strlen(response), 0);
            } else {
                const char *not_found_response = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nName field not found";
                send(client_socket, not_found_response, strlen(not_found_response), 0);
            }
        } else {
            const char *bad_request_response = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nMissing Content-Length header";
            send(client_socket, bad_request_response, strlen(bad_request_response), 0);
        }
    }

    close(client_socket);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    int opt = 1;
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

    while ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))) {
        if (fork() == 0) {
            close(server_fd);
            handle_request(new_socket);
            exit(0);
        }
        close(new_socket);
    }

    return 0;
}
