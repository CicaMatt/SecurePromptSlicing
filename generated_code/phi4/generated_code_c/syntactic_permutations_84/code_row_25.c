#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 4096

void handle_request(const char *request) {
    const char *payload_prefix = "payload=";
    char response[BUFFER_SIZE] = {0};

    if (strstr(request, payload_prefix)) {
        // Extract the payload
        char *payload_start = strstr(request, payload_prefix) + strlen(payload_prefix);
        char payload[BUFFER_SIZE];
        strncpy(payload, payload_start, BUFFER_SIZE - 1);

        // Check if type is Create
        if (strstr(payload, "type: Create")) {
            snprintf(response, sizeof(response), "Error: Type 'Create' not allowed.");
        } else {
            snprintf(response, sizeof(response), "Payload received and processed successfully.");
        }
    } else {
        snprintf(response, sizeof(response), "Error: No payload parameter found.");
    }

    printf("%s\n", response);
}

int main() {
    char buffer[BUFFER_SIZE] = {0};
    
    printf("Listening on port 5000...\n");

    while (fgets(buffer, BUFFER_SIZE, stdin)) {
        handle_request(buffer);
        memset(buffer, 0, BUFFER_SIZE); // Clear the buffer for next input
    }

    return 0;
}