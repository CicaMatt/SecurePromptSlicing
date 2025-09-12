#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 1024
#define MAX_PAYLOAD_LENGTH 512

void parse_url(const char *url, char *payload) {
    const char *start = strstr(url, "?") + 1;
    if (start && strchr(start, '=')) {
        strncpy(payload, start + 1, MAX_PAYLOAD_LENGTH - 1);
        payload[MAX_PAYLOAD_LENGTH - 1] = '\0';
    } else {
        strcpy(payload, "");
    }
}

int main() {
    char url[MAX_URL_LENGTH];
    printf("Enter URL: ");
    fgets(url, sizeof(url), stdin);

    // Remove newline character if present
    size_t len = strlen(url);
    if (len > 0 && url[len - 1] == '\n') {
        url[--len] = '\0';
    }

    char payload[MAX_PAYLOAD_LENGTH];
    parse_url(url, payload);

    // Simulate loading payload into a dictionary and extracting the name value
    const char *key = "name=";
    char *name_start = strstr(payload, key);
    if (name_start) {
        name_start += strlen(key);  // Move past the key
        char *name_end = strchr(name_start, '&');
        if (!name_end) {
            name_end = payload + strlen(payload);
        }
        size_t name_length = name_end - name_start;
        char name_value[name_length + 1];
        strncpy(name_value, name_start, name_length);
        name_value[name_length] = '\0';
        
        printf("Name value: %s\n", name_value);
    } else {
        printf("Name parameter not found.\n");
    }

    return 0;
}