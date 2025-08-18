#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PAYLOAD_SIZE 1024

typedef struct {
    char *name;
} Dictionary;

int main() {
    char payload[MAX_PAYLOAD_SIZE];
    printf("Enter URL with payload (e.g., /api?payload={\"name\":\"John Doe\"}): ");
    fgets(payload, sizeof(payload), stdin);

    // Extracting the payload from the URL
    if (strstr(payload, "/api") == NULL) {
        fprintf(stderr, "Invalid URL. Must start with '/api'.\n");
        return 1;
    }

    char *start = strstr(payload, "?payload=");
    if (!start) {
        fprintf(stderr, "Payload not found in the URL.\n");
        return 1;
    }
    
    // Move to the payload part
    start += strlen("?payload=");

    // Parse JSON-like string
    Dictionary dict;
    dict.name = NULL;

    char *name_start = strstr(start, "\"name\":\"");
    if (!name_start) {
        fprintf(stderr, "Name not found in payload.\n");
        return 1;
    }

    name_start += strlen("\"name\":\"");

    char *name_end = strchr(name_start, '"');
    if (!name_end) {
        fprintf(stderr, "Invalid format for 'name'.\n");
        return 1;
    }

    size_t name_len = name_end - name_start;
    dict.name = (char *)malloc((name_len + 1) * sizeof(char));
    strncpy(dict.name, name_start, name_len);
    dict.name[name_len] = '\0';

    printf("Name: %s\n", dict.name);

    free(dict.name);
    return 0;
}