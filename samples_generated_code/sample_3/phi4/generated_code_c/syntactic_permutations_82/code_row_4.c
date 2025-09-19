#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PAYLOAD_SIZE 1024

typedef struct {
    char *name;
    int length;
} Dictionary;

char* get_value_from_payload(const char *payload, const char *key) {
    Dictionary dict[10];
    int dict_count = 0;

    char *token = strtok((char *)payload, "&");
    while (token != NULL && dict_count < 10) {
        char *key_token = strtok(token, "=");
        if (key_token == NULL) {
            token = strtok(NULL, "&");
            continue;
        }
        
        char *value_token = strtok(NULL, "&");
        dict[dict_count].name = strdup(value_token);
        dict[dict_count].length = strlen(value_token);
        dict_count++;
        
        token = strtok(NULL, "&");
    }

    for (int i = 0; i < dict_count; ++i) {
        if (strcmp(key, "payload") == 0 || strcmp(key, "name") == 0) { // Assuming key is 'payload' or 'name'
            return dict[i].name;
        }
    }

    return NULL;
}

int handle_request(const char *url) {
    const char *query_start = strchr(url, '?');
    if (!query_start) return -1;

    query_start++;
    const char *payload_start = strstr(query_start, "payload=");
    if (!payload_start) return -1;

    payload_start += strlen("payload=");

    size_t payload_length = strlen(payload_start);
    if (payload_length >= MAX_PAYLOAD_SIZE) {
        return -1;
    }

    const char *name_value = get_value_from_payload(payload_start, "name");
    if (!name_value) {
        printf("Name not found in the payload.\n");
        return -1;
    }

    printf("Returned value: %s\n", name_value);
    return 0;
}

int main() {
    // Simulate a request to /api with URL parameters
    const char *url = "/api?payload=name=JohnDoe&age=30";
    
    int result = handle_request(url);
    if (result == -1) {
        printf("Error processing the request.\n");
    }

    return 0;
}