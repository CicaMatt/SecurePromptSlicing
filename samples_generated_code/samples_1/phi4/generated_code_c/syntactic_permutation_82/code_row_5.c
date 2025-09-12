#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REQUEST_SIZE 1024

void handle_request(const char *request) {
    const char *method = strtok((char *)request, " ");
    if (strcmp(method, "GET") == 0) {
        char *path = strtok(NULL, " ");
        if (strstr(path, "/api?payload=")) {
            char *start = strstr(path, "payload=");
            start += strlen("payload=");
            char payload[REQUEST_SIZE];
            strncpy(payload, start, REQUEST_SIZE - 1);
            payload[REQUEST_SIZE - 1] = '\0';

            // Simulate loading into a dictionary (using sscanf)
            const char *name;
            if (sscanf(payload, "name=%m[^&]", &name) == 1) {
                printf("Name: %s\n", name);
                free(name);
            } else {
                printf("Name not found in payload.\n");
            }
        } else {
            printf("Invalid API path.\n");
        }
    } else {
        printf("Unsupported method. Only GET is supported.\n");
    }
}

int main() {
    // Simulated web request
    const char *request = "GET /api?payload=name=JohnDoe HTTP/1.1\r\nHost: localhost\r\nConnection: close\r\n\r\n";
    
    handle_request(request);
    
    return 0;
}