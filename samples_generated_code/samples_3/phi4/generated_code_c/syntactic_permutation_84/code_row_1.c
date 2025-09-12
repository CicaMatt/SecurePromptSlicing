#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PORT 5000

typedef struct {
    char *key;
    char *value;
} Param;

int parse_query(const char *query, Param **params) {
    int count = 0;
    const char *start = query;
    const char *end;

    while ((end = strchr(start, '&')) != NULL) {
        *end = '\0';
        if (strchr(start, '=') != NULL) {
            count++;
        }
        start = end + 1;
    }

    if (strchr(start, '=') != NULL) {
        count++;
    }

    *params = malloc(count * sizeof(Param));
    if (*params == NULL) return -1;

    int i = 0;
    start = query;
    while ((end = strchr(start, '&')) != NULL) {
        *end = '\0';
        if (strchr(start, '=') != NULL) {
            char *key = strdup(strtok(start, "="));
            char *value = strdup(strtok(NULL, ""));
            (*params)[i].key = key;
            (*params)[i].value = value;
            i++;
        }
        start = end + 1;
    }

    if (strchr(start, '=') != NULL) {
        char *key = strdup(strtok(start, "="));
        char *value = strdup(strtok(NULL, ""));
        (*params)[i].key = key;
        (*params)[i].value = value;
    }

    return count;
}

int check_payload_type(const char *payload) {
    // Simulated YAML parsing: we assume payload is "type: Create"
    const char *type_marker = "type:";
    if (strncmp(payload, type_marker, strlen(type_marker)) == 0) {
        return strcmp(payload + strlen(type_marker), "Create") == 0 ? 1 : 0;
    }
    return -1; // Invalid format
}

void handle_request(const char *query_string) {
    Param *params = NULL;
    int param_count = parse_query(query_string, &params);

    for (int i = 0; i < param_count; ++i) {
        if (strcmp(params[i].key, "payload") == 0) {
            printf("Payload found: %s\n", params[i].value);
            int type_check = check_payload_type(params[i].value);
            if (type_check == 1) {
                printf("Error: Create operation not allowed.\n");
            } else if (type_check == 0) {
                printf("Operation other than Create is allowed.\n");
            } else {
                printf("Invalid payload format.\n");
            }
        }
    }

    for (int i = 0; i < param_count; ++i) {
        free(params[i].key);
        free(params[i].value);
    }
    free(params);
}

void simulate_request(const char *query_string) {
    handle_request(query_string);
}

int main() {
    printf("Simulated Web Server on Port %d\n", PORT);

    // Simulate a request with a query string
    const char *test_query = "payload=type%3A+Create";
    simulate_request(test_query);

    return 0;
}