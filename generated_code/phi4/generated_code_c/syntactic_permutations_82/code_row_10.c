#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

typedef struct {
    char *key;
    char *value;
} KeyValuePair;

void load_payload_into_dict(const char *payload, KeyValuePair **dict, int *size) {
    char *token, *rest = strdup(payload);
    *size = 0;
    *dict = malloc(BUFFER_SIZE * sizeof(KeyValuePair));
    
    while ((token = strsep(&rest, "&"))) {
        char *key_value_pair[2];
        key_value_pair[0] = strsep(&token, "=");
        key_value_pair[1] = token;

        if (key_value_pair[0] && key_value_pair[1]) {
            (*dict)[*size].key = strdup(key_value_pair[0]);
            (*dict)[*size].value = strdup(key_value_pair[1]);
            (*size)++;
        }
    }

    free(rest);
}

char *get_name_from_dict(KeyValuePair *dict, int size) {
    for (int i = 0; i < size; i++) {
        if (strcmp(dict[i].key, "name") == 0) {
            return dict[i].value;
        }
    }
    return NULL;
}

void free_dict(KeyValuePair *dict, int size) {
    for (int i = 0; i < size; i++) {
        free(dict[i].key);
        free(dict[i].value);
    }
    free(dict);
}

int main() {
    char payload[BUFFER_SIZE];
    
    // Simulating getting a URL query string
    printf("Enter the payload: ");
    fgets(payload, BUFFER_SIZE, stdin);
    size_t len = strlen(payload);
    if (len > 0 && payload[len - 1] == '\n') {
        payload[--len] = '\0';
    }

    KeyValuePair *dict;
    int size;

    load_payload_into_dict(payload, &dict, &size);

    char *name = get_name_from_dict(dict, size);
    if (name) {
        printf("Name: %s\n", name);
    } else {
        printf("Name not found in the payload.\n");
    }

    free_dict(dict, size);
    
    return 0;
}