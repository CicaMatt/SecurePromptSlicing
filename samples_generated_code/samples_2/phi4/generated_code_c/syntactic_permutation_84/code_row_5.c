#include <arpa/inet.h>
#include <ctype.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 5000

int is_yaml_key(const char *str, const char *key) {
    return strncmp(str, key, strlen(key)) == 0;
}

void handle_request(int client_socket) {
    char buffer[1024] = {0};
    int valread = read(client_socket, buffer, sizeof(buffer));
    
    if (valread > 0 && strstr(buffer, ".yaml")) {
        const char *payload_marker = "payload=";
        char *payload_start = strstr(buffer, payload_marker);
        
        if (payload_start) {
            payload_start += strlen(payload_marker);
            
            // Simulate YAML parsing
            char type[50] = {0};
            if (is_yaml_key(payload_start, "---\ntype: Create\n")) {
                write(client_socket, "Error: Type is Create\n", 23);
            } else {
                write(client_socket, "Request processed\n", 17);
            }
        } else {
            write(client_socket, "Error: No payload found\n", 24);
        }
    } else {
        write(client_socket, "Error: Not a YAML request\n", 25);
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