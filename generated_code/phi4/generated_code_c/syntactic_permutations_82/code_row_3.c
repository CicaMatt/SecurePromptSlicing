#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PORT 8080

void handle_client(int client_fd) {
    char buffer[1024] = {0};
    int bytes_read = read(client_fd, buffer, sizeof(buffer));
    
    if (bytes_read > 0) {
        char *method = strtok(buffer, " ");
        char *path = strtok(NULL, " ");
        
        if (strcmp(method, "GET") == 0 && strstr(path, "/api?payload=")) {
            char *payload_str = strchr(path, '=') + 1;
            char payload[512] = {0};
            
            strncpy(payload, payload_str, sizeof(payload) - 1);
            payload[sizeof(payload) - 1] = '\0';
            
            char *key_value_pairs[] = {"name=John Doe", "age=30"}; // Example dictionary
            int num_pairs = sizeof(key_value_pairs) / sizeof(key_value_pairs[0]);
            
            char response[1024] = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n";
            char name_value[256] = {0};
            
            for (int i = 0; i < num_pairs; ++i) {
                char *pair = key_value_pairs[i];
                char *key = strtok(pair, "=");
                char *value = strtok(NULL, "=");

                if (strcmp(key, "name") == 0 && strstr(payload, value)) {
                    snprintf(name_value, sizeof(name_value), "%s", value);
                    break;
                }
            }

            strcat(response, name_value ? name_value : "Name not found");
            
            write(client_fd, response, strlen(response));
        } else {
            char *response = "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nRoute not found";
            write(client_fd, response, strlen(response));
        }
    }

    close(client_fd);
}

int main() {
    int server_fd, client_fd;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
        perror("socket failed");
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
        client_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (client_fd < 0) {
            perror("accept");
            continue;
        }
        
        handle_client(client_fd);
    }

    close(server_fd);
    return 0;
}