#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <yaml.h>

#define PORT 5000

void handle_client(int client_sock) {
    char buffer[4096];
    int bytes_received = recv(client_sock, buffer, sizeof(buffer), 0);

    if (bytes_received < 1) {
        close(client_sock);
        return;
    }

    buffer[bytes_received] = '\0';

    // Check if payload parameter is present
    const char *payload_start = strstr(buffer, "payload=");
    if (!payload_start) {
        const char *error_msg = "Error: No payload parameter\n";
        send(client_sock, error_msg, strlen(error_msg), 0);
        close(client_sock);
        return;
    }

    // Extract the YAML content from the payload
    payload_start += strlen("payload=");
    yaml_parser_t parser;
    FILE *fp = fmemopen(payload_start, bytes_received - (payload_start - buffer), "r");
    if (!fp) {
        const char *error_msg = "Error: Failed to open memory file\n";
        send(client_sock, error_msg, strlen(error_msg), 0);
        close(client_sock);
        return;
    }

    yaml_parser_initialize(&parser);
    yaml_parser_set_input_file(&parser, fp);

    // Check if the type is Create
    yaml_event_t event;
    if (!yaml_parser_parse(&parser, &event)) {
        const char *error_msg = "Error: Failed to parse YAML\n";
        send(client_sock, error_msg, strlen(error_msg), 0);
        yaml_event_delete(&event);
        fclose(fp);
        close(client_sock);
        return;
    }

    if (event.type == YAML_SCALAR_EVENT) {
        if (!strcmp(event.data.scalar.value, "Create")) {
            const char *error_msg = "Error: Type is Create\n";
            send(client_sock, error_msg, strlen(error_msg), 0);
        } else {
            const char *success_msg = "Success: Payload processed\n";
            send(client_sock, success_msg, strlen(success_msg), 0);
        }
    }

    yaml_event_delete(&event);
    fclose(fp);
    close(client_sock);
}

int main() {
    int server_sock, client_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);

    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(server_sock);
        exit(EXIT_FAILURE);
    }

    if (listen(server_sock, 10) < 0) {
        perror("Listen failed");
        close(server_sock);
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d\n", PORT);

    while (1) {
        client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &client_len);
        if (client_sock < 0) {
            perror("Accept failed");
            continue;
        }
        handle_client(client_sock);
    }

    close(server_sock);
    return 0;
}


**Note:** Make sure to link against the `libyaml` library when compiling this code. Use `-lyaml` with your compiler, e.g., `gcc -o webapp webapp.c -lyaml`.