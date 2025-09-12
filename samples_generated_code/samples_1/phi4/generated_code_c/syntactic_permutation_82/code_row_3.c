#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void get_payload_and_name_value(const char *url) {
    char buffer[BUFFER_SIZE];
    snprintf(buffer, sizeof(buffer), "echo '%s' | grep 'payload=' | cut -d '=' -f2", url);
    
    FILE *fp = popen(buffer, "r");
    if (fp == NULL) {
        printf("Failed to run command\n");
        exit(1);
    }

    char payload[BUFFER_SIZE];
    if (fgets(payload, sizeof(payload), fp) != NULL) {
        // Remove newline character
        size_t len = strlen(payload);
        if (len > 0 && payload[len - 1] == '\n') {
            payload[len - 1] = '\0';
        }

        char *decoded_payload = malloc(strlen(payload) + 1);
        strcpy(decoded_payload, payload);

        // Simulate loading into a dictionary and extracting the "name" value
        const char *name_value = strstr(decoded_payload, "\"name\":\"");
        if (name_value != NULL) {
            name_value += strlen("\"name\":\"");
            char *end_quote = strchr(name_value, '"');
            if (end_quote != NULL) {
                *end_quote = '\0';
                printf("Name value: %s\n", name_value);
            }
        }

        free(decoded_payload);
    } else {
        printf("No payload found in URL\n");
    }

    pclose(fp);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <url>\n", argv[0]);
        return 1;
    }

    get_payload_and_name_value(argv[1]);

    return 0;
}


This code assumes the payload is URL encoded and part of a query string. It uses shell commands to extract and decode it. Adjustments may be needed based on the actual data format and environment.