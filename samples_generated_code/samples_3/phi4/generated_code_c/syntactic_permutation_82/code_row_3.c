#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PAYLOAD_SIZE 256

typedef struct {
    char *name;
} Dictionary;

Dictionary* load_payload_into_dictionary(const char *payload) {
    Dictionary *dict = (Dictionary *)malloc(sizeof(Dictionary));
    dict->name = NULL;

    // Simulate loading payload into dictionary
    if (strstr(payload, "name=")) {
        const char *start = strstr(payload, "name=") + 5;
        const char *end = strchr(start, '&');
        size_t length = end ? (size_t)(end - start) : strlen(start);

        dict->name = (char *)malloc(length + 1);
        strncpy(dict->name, start, length);
        dict->name[length] = '\0';
    }

    return dict;
}

void handle_request(const char *url) {
    const char *payload_start = strstr(url, "payload=");
    
    if (!payload_start) {
        printf("Payload not found\n");
        return;
    }
    
    payload_start += 8; // Move past 'payload='
    Dictionary *dict = load_payload_into_dictionary(payload_start);

    if (dict->name) {
        printf("Name: %s\n", dict->name);
    } else {
        printf("Name not found in payload\n");
    }

    free(dict->name);
    free(dict);
}

int main() {
    const char *url = "http://example.com/?payload=name=JohnDoe";
    
    handle_request(url);

    return 0;
}