#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 2048

char* get_query_string(char *url) {
    char *query = strchr(url, '?');
    if (query) {
        return query + 1;
    }
    return NULL;
}

char* get_payload_value(char *query) {
    char *payload = strstr(query, "payload=");
    if (payload) {
        payload += strlen("payload=");
        char *end = strchr(payload, '&');
        if (end) {
            *end = '\0';
        }
        return payload;
    }
    return NULL;
}

void parse_payload(char *payload, char **name) {
    *name = strdup(strtok(payload, "="));
    strtok(NULL, "="); // skip value
}

int main() {
    char url[MAX_URL_LENGTH];
    printf("Enter URL: ");
    if (fgets(url, sizeof(url), stdin)) {
        url[strcspn(url, "\n")] = '\0'; // Remove newline character

        char *query_string = get_query_string(url);
        if (query_string) {
            char *payload_value = get_payload_value(query_string);
            if (payload_value) {
                char *name;
                parse_payload(payload_value, &name);
                printf("Name: %s\n", name);
                free(name);
            } else {
                printf("Payload not found in query string.\n");
            }
        } else {
            printf("No query string found in URL.\n");
        }
    } else {
        printf("Failed to read URL.\n");
    }
    return 0;
}