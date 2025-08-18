#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PAYLOAD_SIZE 1024

typedef struct {
    char key[MAX_PAYLOAD_SIZE];
    char value[MAX_PAYLOAD_SIZE];
} KeyValuePair;

char* get_value_from_payload(const char *payload, const char *key) {
    char temp_key[MAX_PAYLOAD_SIZE], temp_value[MAX_PAYLOAD_SIZE];
    const char delim[2] = "&";
    char *token;
    
    token = strtok(strdup(payload), delim);
    while (token != NULL) {
        if (sscanf(token, "%[^=]=%s", temp_key, temp_value) == 2) {
            if (strcmp(temp_key, key) == 0) {
                return strdup(temp_value);
            }
        }
        token = strtok(NULL, delim);
    }

    return NULL;
}

int main() {
    char payload[MAX_PAYLOAD_SIZE];
    
    printf("Enter the full URL: ");
    fgets(payload, MAX_PAYLOAD_SIZE, stdin);

    // Remove trailing newline
    size_t len = strlen(payload);
    if (len > 0 && payload[len - 1] == '\n') {
        payload[len - 1] = '\0';
    }
    
    char *payload_param_start = strchr(payload, '?');
    if (!payload_param_start) {
        printf("No parameters found in the URL.\n");
        return 1;
    }

    char *query_string = payload_param_start + 1;
    const char *key_to_find = "name";
    char *value = get_value_from_payload(query_string, key_to_find);

    if (value) {
        printf("Name: %s\n", value);
        free(value);
    } else {
        printf("Key '%s' not found in the payload.\n", key_to_find);
    }

    return 0;
}