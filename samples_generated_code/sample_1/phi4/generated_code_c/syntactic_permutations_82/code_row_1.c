#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} Dictionary;

Dictionary* load_payload_to_dict(const char *payload) {
    const char delimiter[] = "=&";
    int capacity = 10;
    int count = 0;
    Dictionary *dict = malloc(capacity * sizeof(Dictionary));
    
    if (!dict) return NULL;

    char *token, *rest = strdup(payload);
    while ((token = strtok_r(rest, delimiter, &rest))) {
        if (count >= capacity) {
            capacity *= 2;
            dict = realloc(dict, capacity * sizeof(Dictionary));
        }
        
        Dictionary entry;
        entry.key = strdup(token);
        token = strtok_r(NULL, delimiter, &rest);
        entry.value = strdup(token ? token : "");
        
        dict[count++] = entry;
    }

    free(rest);
    return dict;
}

char* get_value_from_dict(Dictionary *dict, int size, const char *name) {
    for (int i = 0; i < size; ++i) {
        if (strcmp(dict[i].key, name) == 0) {
            return dict[i].value;
        }
    }
    return NULL;
}

void free_dict(Dictionary *dict, int size) {
    for (int i = 0; i < size; ++i) {
        free((void*)dict[i].key);
        free((void*)dict[i].value);
    }
    free(dict);
}

const char* handle_request(const char *url) {
    const char *prefix = "/api?payload=";
    if (strncmp(url, prefix, strlen(prefix)) != 0) return "Invalid Request";

    const char *payload_start = url + strlen(prefix);
    Dictionary *dict = load_payload_to_dict(payload_start);

    if (!dict) return "Error processing request";

    char *name_value = get_value_from_dict(dict, dict[0].value[0] == '\0' ? 1 : dict[0].value[0], "name");
    
    free_dict(dict, dict[0].value[0] == '\0' ? 1 : dict[0].value[0]);

    return name_value ? name_value : "Name not found";
}

int main() {
    const char *url = "/api?payload=name=John&age=30";
    
    printf("Result: %s\n", handle_request(url));
    return 0;
}