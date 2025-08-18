#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PAYLOAD_LENGTH 1024

typedef struct {
    char *name;
} Dictionary;

Dictionary load_payload_into_dictionary(const char *payload) {
    Dictionary dict;
    dict.name = NULL;

    if (strstr(payload, "name=") != NULL) {
        const char *start = strstr(payload, "name=");
        start += 5; // Skip past 'name='
        const char *end = strchr(start, '&');
        size_t length = end ? (size_t)(end - start) : strlen(start);

        dict.name = malloc(length + 1);
        strncpy(dict.name, start, length);
        dict.name[length] = '\0';
    }

    return dict;
}

const char* get_name_from_dictionary(Dictionary *dict) {
    return dict->name;
}

void handle_request(const char *url) {
    const char *payload_start = strchr(url, '?');
    if (!payload_start) {
        printf("Payload not found\n");
        return;
    }

    payload_start++; // Move past the '?'
    Dictionary dict = load_payload_into_dictionary(payload_start);

    const char *name = get_name_from_dictionary(&dict);
    if (name) {
        printf("Name: %s\n", name);
    } else {
        printf("Name not found in payload\n");
    }

    free(dict.name);
}

int main() {
    // Simulate a web app route being hit
    const char *url = "http://example.com/?name=JohnDoe";
    handle_request(url);

    return 0;
}