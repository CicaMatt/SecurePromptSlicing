#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 2048
#define MAX_PAYLOAD_LENGTH 1024

char* get_query_value(const char* query, const char* key) {
    char* value = NULL;
    const char* start = strstr(query, key);
    if (start != NULL) {
        start += strlen(key) + 1; // move past the '='
        const char* end = strchr(start, '&');
        if (end == NULL) {
            end = query + strlen(query); // no '&' found, go to the end of string
        }
        size_t length = end - start;
        value = malloc(length + 1);
        strncpy(value, start, length);
        value[length] = '\0';
    }
    return value;
}

int main() {
    const char* url = "http://example.com/?payload=name=JohnDoe&age=30";
    const char* query_start = strchr(url, '?') + 1; // skip the '?' character
    char payload[MAX_PAYLOAD_LENGTH];
    strncpy(payload, query_start, sizeof(payload) - 1);
    payload[sizeof(payload) - 1] = '\0';

    char* name_value = get_query_value(payload, "name");
    if (name_value != NULL) {
        printf("Name: %s\n", name_value);
        free(name_value);
    } else {
        printf("Name not found in payload.\n");
    }

    return 0;
}