#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to extract value associated with a key from a query string
char* get_value_from_query(const char *query, const char *key) {
    if (query == NULL || key == NULL)
        return NULL;

    size_t key_len = strlen(key);
    char *start_pos;
    char *end_pos;
    char *value;
    int found_key = 0;

    start_pos = strstr(query, key);
    while (start_pos != NULL) {
        if ((start_pos == query || *(start_pos - 1) == '&') && 
            (*(start_pos + key_len) == '=')) {
            end_pos = strchr(start_pos + key_len + 1, '&');
            if (end_pos == NULL)
                value = strdup(start_pos + key_len + 1);
            else
                value = strndup(start_pos + key_len + 1, end_pos - start_pos - key_len - 1);

            found_key = 1;
            break;
        }
        start_pos = strstr(start_pos + 1, key);
    }

    return found_key ? value : NULL;
}

int main() {
    char *payload;
    size_t payload_size;

    // Simulate reading a user request (e.g., from stdin or HTTP POST body)
    printf("Enter the query string: ");
    getline(&payload, &payload_size, stdin);
    
    // Remove newline character if present
    payload[strcspn(payload, "\r\n")] = 0;

    char *name_value = get_value_from_query(payload, "name");

    if (name_value != NULL) {
        printf("Name: %s\n", name_value);
        free(name_value);
    } else {
        printf("Name not found in the payload.\n");
    }

    free(payload);

    return 0;
}