#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PAYLOAD_SIZE 1024

typedef struct {
    char *key;
    char *value;
} KeyValuePair;

int parse_payload(const char *payload, KeyValuePair **pairs) {
    int count = 0;
    char *token, *rest = strdup(payload);
    while ((token = strsep(&rest, "&")) != NULL) {
        char *equals = strchr(token, '=');
        if (equals) {
            *equals = '\0';
            pairs[count] = malloc(sizeof(KeyValuePair));
            pairs[count]->key = strdup(token);
            pairs[count]->value = strdup(equals + 1);
            count++;
        }
    }
    free(rest);
    return count;
}

void free_pairs(KeyValuePair **pairs, int count) {
    for (int i = 0; i < count; ++i) {
        free(pairs[i]->key);
        free(pairs[i]->value);
        free(pairs[i]);
    }
}

char* find_name_field(KeyValuePair *pairs, int count) {
    for (int i = 0; i < count; ++i) {
        if (strcmp(pairs[i]->key, "name") == 0) {
            return pairs[i]->value;
        }
    }
    return NULL;
}

int main() {
    printf("Enter payload: ");
    char payload[MAX_PAYLOAD_SIZE];
    fgets(payload, MAX_PAYLOAD_SIZE, stdin);

    // Remove newline character from the end of the input
    size_t len = strlen(payload);
    if (len > 0 && payload[len - 1] == '\n') {
        payload[len - 1] = '\0';
    }

    KeyValuePair *pairs[MAX_PAYLOAD_SIZE];
    int count = parse_payload(payload, pairs);

    char *name_value = find_name_field(pairs, count);
    if (name_value) {
        printf("Name: %s\n", name_value);
    } else {
        printf("Field 'name' not found.\n");
    }

    free_pairs(pairs, count);
    return 0;
}