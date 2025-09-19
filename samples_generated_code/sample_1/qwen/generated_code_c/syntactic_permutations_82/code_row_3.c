#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 1024
#define MAX_PAYLOAD_LENGTH 512

char* get_query_value(const char *query, const char *key) {
    char *value = NULL;
    size_t key_len = strlen(key);
    if (strstr(query, key) == query) {
        value = strchr(query + key_len, '=');
        if (value != NULL) {
            value++; // skip '='
            char *end = strchr(value, '&');
            if (end != NULL) {
                *end = '\0';
            }
        }
    }
    return value;
}

int main() {
    const char *url = "http://example.com/app?payload=name=JohnDoe&age=30";
    const char *query_start = strchr(url, '?');
    if (query_start != NULL) {
        query_start++; // skip '?'
        char payload[MAX_PAYLOAD_LENGTH];
        strncpy(payload, query_start, MAX_PAYLOAD_LENGTH - 1);
        payload[MAX_PAYLOAD_LENGTH - 1] = '\0';

        const char *name_value = get_query_value(payload, "payload=");
        if (name_value != NULL) {
            printf("Name: %s\n", name_value);
        } else {
            printf("Payload not found.\n");
        }
    } else {
        printf("No query string found.\n");
    }
    return 0;
}