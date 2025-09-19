#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 2048
#define MAX_PAYLOAD_LENGTH 1024

char* get_query_string(const char *url) {
    const char *query_start = strchr(url, '?');
    if (query_start == NULL) return NULL;
    return strdup(query_start + 1);
}

void parse_payload(char *payload, char **name_value) {
    char *token = strtok(payload, "&");
    while (token != NULL) {
        if (strncmp(token, "name=", 5) == 0) {
            *name_value = strdup(token + 5);
            break;
        }
        token = strtok(NULL, "&");
    }
}

int main() {
    char url[MAX_URL_LENGTH];
    printf("Enter URL: ");
    fgets(url, MAX_URL_LENGTH, stdin);
    url[strcspn(url, "\n")] = '\0';

    char *query_string = get_query_string(url);
    if (query_string == NULL) {
        fprintf(stderr, "No query string found in the URL.\n");
        return 1;
    }

    char payload[MAX_PAYLOAD_LENGTH];
    snprintf(payload, MAX_PAYLOAD_LENGTH, "%s", query_string);

    char *name_value = NULL;
    parse_payload(payload, &name_value);
    if (name_value == NULL) {
        fprintf(stderr, "No name parameter found in the payload.\n");
        free(query_string);
        return 1;
    }

    printf("Name: %s\n", name_value);

    free(name_value);
    free(query_string);
    return 0;
}