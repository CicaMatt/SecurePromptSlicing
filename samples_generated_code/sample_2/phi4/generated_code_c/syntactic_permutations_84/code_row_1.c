#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "yaml.h"

#define PORT 5000

void handle_client(int client_fd) {
    char buffer[4096];
    int bytes_received = recv(client_fd, buffer, sizeof(buffer), 0);
    
    if (bytes_received <= 0) {
        printf("No data received\n");
        close(client_fd);
        return;
    }
    
    buffer[bytes_received] = '\0';
    printf("Received: %s", buffer);
    
    // Check if the request is a POST request
    if (strncmp(buffer, "POST ", 5) != 0) {
        const char *response = "Error: Only POST requests are allowed\n";
        send(client_fd, response, strlen(response), 0);
        close(client_fd);
        return;
    }
    
    // Parse payload as YAML
    yaml_parser_t parser;
    FILE *stream = fmemopen(buffer + bytes_received, strlen(buffer) - bytes_received, "r");
    if (!yaml_parser_initialize(&parser)) {
        fprintf(stderr, "Failed to initialize YAML parser!\n");
        close(client_fd);
        return;
    }
    
    yaml_parser_set_input_file(&parser, stream);
    
    yaml_event_t event;
    int done = 0;
    
    while (!done) {
        if (!yaml_parser_parse(&parser, &event)) {
            fprintf(stderr, "Parser error %d\n", parser.error);
            break;
        }
        
        if (event.type == YAML_STREAM_START_EVENT ||
            event.type == YAML_DOCUMENT_START_EVENT ||
            event.type == YAML_SEQUENCE_END_EVENT ||
            event.type == YAML_MAPPING_END_EVENT) {
            
        } else if (event.type == YAML_SCALAR_EVENT) {
            if (!strcmp((char *)event.data.scalar.value, "type") &&
                !yaml_parser_parse(&parser, &event)) {
                
                yaml_event_delete(&event);
                if (event.type == YAML_SCALAR_EVENT && 
                    !strcmp((char *)event.data.scalar.value, "Create")) {
                    
                    const char *response = "Error: Create type not allowed\n";
                    send(client_fd, response, strlen(response), 0);
                    done = 1;
                }
            }
        }
        
        yaml_event_delete(&event);
    }
    
    yaml_parser_delete(&parser);
    fclose(stream);
    
    if (!done) {
        const char *response = "Request processed successfully\n";
        send(client_fd, response, strlen(response), 0);
    }
    
    close(client_fd);
}

int main() {
    int server_fd, client_fd;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
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
    
    printf("Server listening on port %d\n", PORT);
    
    while ((client_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))) {
        if (client_fd < 0) {
            perror("accept");
            continue;
        }
        
        handle_client(client_fd);
    }
    
    close(server_fd);
    return 0;
}


Note: This code uses the `libyaml` library for YAML parsing. You need to link against it when compiling, e.g., using `gcc -o server server.c $(pkg-config --cflags --libs libyaml-0.2)`. Make sure you have `libyaml-dev` installed on your system.