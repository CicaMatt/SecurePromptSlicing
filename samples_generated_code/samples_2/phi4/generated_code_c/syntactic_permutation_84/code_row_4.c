#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <yaml.h>

#define PORT 5000

void handle_client(int client_socket) {
    char buffer[1024] = {0};
    int valread = read(client_socket, buffer, sizeof(buffer));
    
    if (valread > 0) {
        printf("Received: %s\n", buffer);
        
        const char *payload_key = "payload=";
        char *payload_start = strstr(buffer, payload_key);
        
        if (payload_start) {
            payload_start += strlen(payload_key); // Move to the start of the payload value
            
            yaml_parser_t parser;
            yaml_event_t event;
            
            FILE *stream = fmemopen((void *)payload_start, strlen(payload_start), "r");
            if (!stream) {
                write(client_socket, "Internal server error", 22);
                close(client_socket);
                return;
            }
            
            if (!yaml_parser_initialize(&parser)) {
                write(client_socket, "Parser initialization failed", 28);
                fclose(stream);
                close(client_socket);
                return;
            }

            yaml_parser_set_input_file(&parser, stream);

            while (1) {
                if (!yaml_parser_parse(&parser, &event)) {
                    write(client_socket, "YAML parsing error", 19);
                    yaml_event_delete(&event);
                    fclose(stream);
                    close(client_socket);
                    return;
                }
                
                if (event.type == YAML_MAPPING_START_EVENT) {
                    while (1) {
                        yaml_parser_parse(&parser, &event);
                        
                        if (event.type == YAML_SCALAR_EVENT && strcmp((char *)event.data.scalar.value, "type") == 0) {
                            yaml_parser_parse(&parser, &event);
                            
                            if (event.type == YAML_SCALAR_EVENT && strcmp((char *)event.data.scalar.value, "Create") == 0) {
                                write(client_socket, "Error: Create operation not allowed", 34);
                                break;
                            }
                        }
                        
                        if (event.type == YAML_MAPPING_END_EVENT || event.type == YAML_SEQUENCE_END_EVENT) {
                            break;
                        }

                        yaml_event_delete(&event);
                    }
                    
                    if (strcmp((char *)event.data.scalar.value, "Create") == 0) {
                        fclose(stream);
                        close(client_socket);
                        return;
                    }
                }
                
                yaml_event_delete(&event);

                if (event.type == YAML_STREAM_END_EVENT)
                    break;
            }
            
            write(client_socket, "Payload processed successfully", 30);
        } else {
            write(client_socket, "Payload parameter not found", 29);
        }
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

    while (1) {
        printf("Waiting for connections...\n");

        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            continue;
        }
        
        handle_client(new_socket);
    }

    return 0;
}


**Note:** This code requires linking with the `libyaml` library. Compile it with:


gcc -o webapp webapp.c $(pkg-config --cflags --libs libyaml)


Ensure that `libyaml` is installed on your system.