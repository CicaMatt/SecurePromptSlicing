#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PORT 5000

void handle_request(const char *request) {
    char *payload_start;
    char *payload_end;

    if ((payload_start = strstr(request, "payload=")) != NULL) {
        payload_start += strlen("payload=");
        
        // Find the end of the URL
        if ((payload_end = strchr(payload_start, '&')) != NULL) {
            size_t payload_length = payload_end - payload_start;
            char *payload = (char *)malloc(payload_length + 1);
            strncpy(payload, payload_start, payload_length);
            payload[payload_length] = '\0';

            // Simulate YAML parsing by checking for a specific structure
            if (strncmp(payload, "type: Create", 12) == 0) {
                printf("Error: 'Create' type is not allowed.\n");
            } else {
                printf("Payload received and processed successfully.\n");
            }

            free(payload);
        } else {
            // Handle case where payload extends to end of request
            char *payload = strdup(payload_start);
            if (strncmp(payload, "type: Create", 12) == 0) {
                printf("Error: 'Create' type is not allowed.\n");
            } else {
                printf("Payload received and processed successfully.\n");
            }
            free(payload);
        }
    } else {
        printf("Error: No payload parameter found in request.\n");
    }
}

int main() {
    char *dummy_request_1 = "GET / HTTP/1.1\r\nHost: localhost\r\nConnection: close\r\npayload=type: Create\r\n";
    char *dummy_request_2 = "GET / HTTP/1.1\r\nHost: localhost\r\nConnection: close\r\n\r\n";
    char *dummy_request_3 = "GET / HTTP/1.1\r\nHost: localhost\r\nConnection: close\r\npayload=type: Read\r\n";

    printf("Test 1:\n");
    handle_request(dummy_request_1);

    printf("\nTest 2:\n");
    handle_request(dummy_request_2);

    printf("\nTest 3:\n");
    handle_request(dummy_request_3);

    return 0;
}