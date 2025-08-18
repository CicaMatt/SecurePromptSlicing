#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* get_query_param(char *query, const char *param) {
    char *token = strtok(query, "&");
    while (token != NULL) {
        char *key = strtok(token, "=");
        if (strcmp(key, param) == 0) {
            char *value = strtok(NULL, "=");
            return value;
        }
        token = strtok(NULL, "&");
    }
    return NULL;
}

char* load_payload_into_dict(char *query) {
    char *name_value = get_query_param(query, "payload");
    if (name_value != NULL) {
        // Assume the payload is in the format name=value
        char *name_key = strtok(name_value, "=");
        if (strcmp(name_key, "name") == 0) {
            return strtok(NULL, "=");
        }
    }
    return NULL;
}

int main() {
    char query[1024];
    printf("Enter the URL query string: ");
    fgets(query, sizeof(query), stdin);
    // Remove newline character
    query[strcspn(query, "\n")] = 0;

    char *name_value = load_payload_into_dict(query);

    if (name_value != NULL) {
        printf("Name value from payload: %s\n", name_value);
    } else {
        printf("No name value found in payload.\n");
    }

    return 0;
}