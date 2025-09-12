#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

void handle_request(const char *url) {
    char *payload = NULL;
    size_t payload_len = 0;

    // Extracting the payload parameter from the URL
    const char *start = strstr(url, "payload=");
    if (start) {
        start += strlen("payload=");
        payload = strndup(start, MAX_LINE_LENGTH - (start - url));
    }

    if (payload && *payload) {
        // Split the payload into a key-value pair
        char *name = strtok(payload, "=");
        char *value = strtok(NULL, "&");

        // Simulating dictionary with simple string check
        if (strcmp(name, "name") == 0 && value) {
            printf("Name: %s\n", value);
        } else {
            printf("Name parameter not found in payload.\n");
        }
    } else {
        printf("No payload parameter found in URL.\n");
    }

    free(payload);
}

int main() {
    const char *url = "http://example.com?payload=name=JohnDoe&age=30";
    handle_request(url);

    return 0;
}