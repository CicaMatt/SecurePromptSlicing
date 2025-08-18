#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PARAMS 100
#define BUFFER_SIZE 1024

typedef struct {
    char *key;
    char *value;
} Param;

char* get_param_value(char *url, const char *param_name) {
    char *query = strchr(url, '?');
    if (!query) return NULL;
    
    query++; // Skip the '?' character
    char buffer[BUFFER_SIZE];
    strncpy(buffer, query, BUFFER_SIZE - 1);
    buffer[strcspn(buffer, " \t\n\r")] = '\0';

    Param params[MAX_PARAMS];
    int param_count = 0;

    char *token = strtok(buffer, "&");
    while (token && param_count < MAX_PARAMS) {
        char *equal_sign = strchr(token, '=');
        if (!equal_sign) break;

        *equal_sign = '\0';
        params[param_count].key = strdup(token);
        params[param_count].value = strdup(equal_sign + 1);
        token = strtok(NULL, "&");
        param_count++;
    }

    for (int i = 0; i < param_count; ++i) {
        if (strcmp(params[i].key, param_name) == 0) {
            char *result = malloc(strlen(params[i].value) + 1);
            strcpy(result, params[i].value);

            // Free allocated memory
            for (int j = 0; j < param_count; ++j) {
                free(params[j].key);
                free(params[j].value);
            }

            return result;
        }
    }

    // Free allocated memory
    for (int i = 0; i < param_count; ++i) {
        free(params[i].key);
        free(params[i].value);
    }

    return NULL;
}

void handle_request(char *url, char *param_name) {
    char *value = get_param_value(url, param_name);

    if (value) {
        printf("Value: %s\n", value);
        free(value);
    } else {
        printf("Parameter '%s' not found.\n", param_name);
    }
}

int main() {
    char url[] = "http://example.com/api?name=John&age=30";
    char *param_name = "name";

    handle_request(url, param_name);

    return 0;
}