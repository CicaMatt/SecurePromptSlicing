#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_URL_LENGTH 256
#define MAX_PAYLOAD_LENGTH 128

char* get_query_value(const char *query, const char *key) {
    char *start = strstr(query, key);
    if (start == NULL) return NULL;

    start += strlen(key) + 1; // Move past the key and '='
    char *end = strchr(start, '&');
    if (end != NULL) {
        int length = end - start;
        char *value = malloc(length + 1);
        strncpy(value, start, length);
        value[length] = '\0';
        return value;
    } else {
        return strdup(start);
    }
}

int main() {
    char url[MAX_URL_LENGTH] = "http://example.com/?payload=name=John&age=30";
    char payload[MAX_PAYLOAD_LENGTH];

    // Extract the query part of the URL
    char *query_start = strchr(url, '?');
    if (query_start == NULL) {
        fprintf(stderr, "No query string found in URL.\n");
        return 1;
    }
    strcpy(payload, query_start + 1);

    // Parse the payload to get the 'name' value
    char *name_value = get_query_value(payload, "name");
    if (name_value != NULL) {
        printf("Name: %s\n", name_value);
        free(name_value);
    } else {
        fprintf(stderr, "'name' key not found in payload.\n");
    }

    return 0;
}