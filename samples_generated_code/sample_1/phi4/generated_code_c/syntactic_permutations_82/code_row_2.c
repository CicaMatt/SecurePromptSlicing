#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PAYLOAD_SIZE 1024

typedef struct {
    char *key;
    char *value;
} KeyValuePair;

int parse_payload(const char *payload, KeyValuePair **dict) {
    const char *delimiter = ", ";
    char *token;
    char *rest = strdup(payload);
    int count = 0;

    while ((token = strtok_r(rest, delimiter, &rest))) {
        if (strchr(token, '=')) {
            char *key = strndup(token, strchr(token, '=') - token);
            char *value = strdup(strchr(token, '=') + 1);

            dict[count] = malloc(sizeof(KeyValuePair));
            dict[count]->key = key;
            dict[count]->value = value;

            count++;
        }
    }

    return count;
}

const char* get_name_value(const KeyValuePair *dict, int size) {
    for (int i = 0; i < size; i++) {
        if (strcmp(dict[i].key, "name") == 0) {
            return dict[i].value;
        }
    }
    return NULL;
}

void handle_request(const char *request_payload) {
    KeyValuePair *dict[100];
    int size = parse_payload(request_payload, dict);

    const char *name_value = get_name_value(dict, size);
    if (name_value) {
        printf("Name: %s\n", name_value);
    } else {
        printf("Name not found in payload.\n");
    }

    for (int i = 0; i < size; i++) {
        free(dict[i]->key);
        free(dict[i]->value);
        free(dict[i]);
    }
}

int main() {
    const char *request_payload = "name=John Doe, age=30";
    handle_request(request_payload);

    return 0;
}