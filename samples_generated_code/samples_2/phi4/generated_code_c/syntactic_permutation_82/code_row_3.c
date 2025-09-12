#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PAYLOAD_SIZE 1024

typedef struct {
    char *name;
    char *value;
} KeyValuePair;

KeyValuePair* load_payload_to_dict(const char *payload, int *size) {
    KeyValuePair *dict = NULL;
    char *token;
    const char delim[] = "&";
    char *payload_copy = strdup(payload);
    
    if (!payload_copy) return NULL;

    token = strtok(payload_copy, delim);
    while (token != NULL) {
        char *key_value_pair = strdup(token);
        char *equals_sign = strchr(key_value_pair, '=');

        if (equals_sign) {
            *equals_sign = '\0';
            KeyValuePair pair;
            pair.name = strdup(token);
            pair.value = strdup(equals_sign + 1);
            dict = realloc(dict, (*size + 1) * sizeof(KeyValuePair));
            dict[*size] = pair;
            (*size)++;
        }
        
        free(key_value_pair);
        token = strtok(NULL, delim);
    }

    free(payload_copy);
    return dict;
}

void free_dict(KeyValuePair *dict, int size) {
    for (int i = 0; i < size; i++) {
        free(dict[i].name);
        free(dict[i].value);
    }
    free(dict);
}

char* get_value_from_dict(KeyValuePair *dict, int size, const char *key) {
    for (int i = 0; i < size; i++) {
        if (strcmp(dict[i].name, key) == 0) {
            return dict[i].value;
        }
    }
    return NULL;
}

void handle_request(const char *payload) {
    int size = 0;
    KeyValuePair *dict = load_payload_to_dict(payload, &size);
    
    if (dict) {
        const char *name_key = "name";
        char *name_value = get_value_from_dict(dict, size, name_key);

        if (name_value) {
            printf("Name: %s\n", name_value);
        } else {
            printf("Key 'name' not found in payload.\n");
        }

        free_dict(dict, size);
    } else {
        printf("Failed to load payload into dictionary.\n");
    }
}

int main() {
    const char *url_payload = "name=JohnDoe&age=30"; // Example URL-encoded payload
    handle_request(url_payload);

    return 0;
}