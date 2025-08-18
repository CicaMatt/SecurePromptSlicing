#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PAYLOAD_SIZE 1024

typedef struct {
    char *key;
    char *value;
} KeyValuePair;

void handle_request(const char* request) {
    // Simulating URL parsing and payload extraction
    const char *payload_start = strstr(request, "payload=");
    if (payload_start == NULL) {
        printf("Payload not found\n");
        return;
    }

    payload_start += 8; // Move past 'payload='
    size_t payload_length = strlen(payload_start);
    if (payload_length > MAX_PAYLOAD_SIZE) {
        printf("Payload too large\n");
        return;
    }

    char *payload = malloc(payload_length + 1);
    strncpy(payload, payload_start, payload_length);
    payload[payload_length] = '\0';

    // Simulating dictionary parsing
    KeyValuePair dict[10]; // Assuming a maximum of 10 key-value pairs for simplicity
    int count = 0;
    
    char *token = strtok(payload, "&");
    while (token != NULL) {
        if (count >= 10) break; // Prevent overflow

        char *key = strdup(token);
        char *value_start = strchr(key, '=');
        if (value_start == NULL) {
            free(key);
            token = strtok(NULL, "&");
            continue;
        }
        
        *value_start = '\0';
        value_start++;

        dict[count].key = key;
        dict[count].value = strdup(value_start);

        count++;
        token = strtok(NULL, "&");
    }

    // Find and print the 'name' value
    for (int i = 0; i < count; i++) {
        if (strcmp(dict[i].key, "name") == 0) {
            printf("Name: %s\n", dict[i].value);
            break;
        }
    }

    // Free allocated memory
    for (int i = 0; i < count; i++) {
        free(dict[i].key);
        free(dict[i].value);
    }
    free(payload);
}

int main() {
    const char *request = "GET /api?payload=name=JohnDoe&age=30 HTTP/1.1";
    handle_request(request);

    return 0;
}