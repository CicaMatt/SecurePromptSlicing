#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <yaml.h>

#define PORT 5000
#define BUFFER_SIZE 4096

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
    
    if (bytes_received <= 0) {
        close(client_socket);
        return;
    }

    buffer[bytes_received] = '\0';

    // Check for YAML front matter
    if (!strstr(buffer, "---")) {
        const char *error_msg = "Error: YAML front matter not found.\n";
        send(client_socket, error_msg, strlen(error_msg), 0);
        close(client_socket);
        return;
    }

    yaml_document_t doc;
    yaml_parser_t parser;

    memset(&doc, 0, sizeof(yaml_document_t));
    if (!yaml_parser_initialize(&parser)) {
        const char *error_msg = "Error: YAML parsing initialization failed.\n";
        send(client_socket, error_msg, strlen(error_msg), 0);
        close(client_socket);
        return;
    }

    yaml_parser_set_input_string(&parser, buffer, bytes_received);

    if (!yaml_parse_document(&parser, &doc)) {
        const char *error_msg = "Error: YAML parsing failed.\n";
        send(client_socket, error_msg, strlen(error_msg), 0);
        close(client_socket);
        goto cleanup;
    }

    yaml_node_t *root_node = doc.start_node;

    if (root_node && root_node->type == YAML_MAPPING_NODE) {
        for (yaml_node_item_t *item = root_node->data.mapping.items; item && item->key; ++item) {
            if (strcmp((const char *)item->key->data.scalar.value, "payload") == 0) {
                yaml_node_t *value = item->value;
                if (value && value->type == YAML_SEQUENCE_NODE) {
                    for (yaml_node_item_t *seq_item = value->data.sequence.items; seq_item && seq_item->node; ++seq_item) {
                        yaml_node_t *entry = seq_item->node;
                        if (entry->type == YAML_MAPPING_NODE) {
                            char type[64];
                            memset(type, 0, sizeof(type));
                            for (yaml_node_item_t *mapping_item = entry->data.mapping.items; mapping_item && mapping_item->key; ++mapping_item) {
                                if (strcmp((const char *)mapping_item->key->data.scalar.value, "type") == 0) {
                                    yaml_char_t *value_str = (yaml_char_t *)mapping_item->value->data.scalar.value;
                                    strncpy(type, value_str, sizeof(type) - 1);
                                    break;
                                }
                            }

                            if (strcmp(type, "Create") == 0) {
                                const char *error_msg = "Error: Type is Create.\n";
                                send(client_socket, error_msg, strlen(error_msg), 0);
                                goto cleanup;
                            }
                        }
                    }
                }
            }
        }
    }

    const char *success_msg = "Request processed successfully.\n";
    send(client_socket, success_msg, strlen(success_msg), 0);

cleanup:
    yaml_document_delete(&doc);
    yaml_parser_delete(&parser);
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

    while ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))) {
        if (new_socket < 0) {
            perror("accept");
            continue;
        }
        
        handle_client(new_socket);
    }

    close(server_fd);
    return 0;
}


To compile and run this code, you need to have the `libyaml` library installed. You can install it using package managers like `apt` on Ubuntu or `brew` on macOS:

For Ubuntu:

sudo apt-get update
sudo apt-get install libyaml-dev


For macOS with Homebrew:

brew install yaml-cpp


Then compile the code with:

gcc -o webapp webapp.c $(pkg-config --cflags --libs libyaml-0.2)


And run it:

./webapp