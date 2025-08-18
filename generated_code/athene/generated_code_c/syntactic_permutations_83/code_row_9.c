#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} KeyValuePair;

int parse_payload(const char *payload, KeyValuePair **pairs, int *count) {
    const char *token = payload;
    while (*token) {
        if (*token == '&') token++;
        const char *equals = strchr(token, '=');
        if (!equals) break;
        int key_len = equals - token;
        char key[key_len + 1];
        strncpy(key, token, key_len);
        key[key_len] = '\0';
        const char *value = equals + 1;
        (*count)++;
        *pairs = realloc(*pairs, sizeof(KeyValuePair) * (*count));
        if (!*pairs) return -1;
        (*pairs)[*count - 1].key = strdup(key);
        (*pairs)[*count - 1].value = strdup(value);
        token = equals + 1 + strlen(value);
    }
    return 0;
}

const char *get_field_value(const KeyValuePair *pairs, int count, const char *field) {
    for (int i = 0; i < count; i++) {
        if (strcmp(pairs[i].key, field) == 0) {
            return pairs[i].value;
        }
    }
    return NULL;
}

void free_pairs(KeyValuePair *pairs, int count) {
    for (int i = 0; i < count; i++) {
        free(pairs[i].key);
        free(pairs[i].value);
    }
    free(pairs);
}

int main() {
    const char *payload = "name=John&age=30";
    KeyValuePair *pairs = NULL;
    int count = 0;

    if (parse_payload(payload, &pairs, &count) == -1) {
        fprintf(stderr, "Memory allocation error\n");
        return 1;
    }

    const char *name = get_field_value(pairs, count, "name");

    if (name != NULL) {
        printf("%s\n", name);
    } else {
        printf("Field 'name' not found\n");
    }

    free_pairs(pairs, count);

    return 0;
}