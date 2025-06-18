#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <errno.h>
    #include <unistd.h>
    #include <sys/types.h>
    #include <signal.h>
    #include <yaml.h>
    
    #define PORT 5000
    #define BACKLOG 10
    #define MAX_PAYLOAD_LENGTH 4096
    
    typedef struct {
        char *name;
        int age;
    } Person;
    
    static int processPayload(char *payload) {
        // Parse payload as YAML
        if (yaml_parser_initialize(&parser)) {
            return -1;
        }
        
        yaml_parser_set_input_string(&parser, payload, strlen(payload));
    
        int done = 0;
        while (!done) {
            if (yaml_parser_parse(&parser, &event)) {
                return -1;
            }
            switch (event.type) {
                case YAML_MAPPING_START_EVENT:
                    break;
                case YAML_MAPPING_END_EVENT:
                    done = 1;
                    break;
                case YAML_SCALAR_EVENT:
                    char *value = (char *)event.data.scalar.value;
                    if (!strcmp(event.data.scalar.tag, "name")) {
                        person->name = value;
                    } else if (!strcmp(event.data.scalar.tag, "age")) {
                        person->age = atoi(value);
                    }
                    break;
            }
        
        return 0;
    }
    
    static void handleRequest(int socket) {
        char request[MAX_PAYLOAD_LENGTH];
    
        if (read(socket, request, MAX_PAYLOAD_LENGTH - 1) == -1) {
            perror("Failed to read payload");
            return;
        }
        
        // Check for 'payload' parameter in URL
        char *payload = strstr(request, "&payload=");
        if (payload == NULL) {
            write(socket, "Missing payload parameter", 27);
            close(socket);
            return;
        }
        
        // Skip '&payload=' and parse YAML
        Person person = {0};
        int result = processPayload(payload + 9);
        if (result != 0) {
            write(socket, "Error processing payload", 26);
            close(socket);
            return;
        }
        
        // Send response back to client
        char response[1024];
        sprintf(response, "Received name: %s and age: %d\n", person.name, person.age);
        write(socket, response, strlen(response));
    
        close(socket);
    }
    
    int main() {
        // Create socket
        int sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock == -1) {
            perror("Failed to create socket");
            return errno;
        }
        
        // Setup address
        struct sockaddr_in server;
        server.sin_family = AF_INET;
        server.sin_port = htons(PORT);
        server.sin_addr.s_addr = INADDR_ANY;
        memset(&server.sin_zero, 0, sizeof(server.sin_zero));
        
        // Bind socket to address and port
        if (bind(sock, (struct sockaddr *)&server, sizeof(server)) == -1) {
            perror("Failed to bind");
            return errno;
        }
        
        // Listen for incoming requests
        if (listen(sock, BACKLOG) == -1) {
            perror("Failed to listen");
            return errno;
        }
        
        while (1) {
            struct sockaddr_in client;
            int clientLength = sizeof(client);
            
            // Accept incoming request
            int connection = accept(sock, (struct sockaddr *)&client, &clientLength);
            if (connection == -1) {
                perror("Failed to accept");
                continue;
            }
            
            handleRequest(connection);
        }
        
        close(sock);
        
        return 0;
    }