#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    int size;
} Dictionary;

Dictionary* create_dictionary() {
    Dictionary *dict = malloc(sizeof(Dictionary));
    dict->name = NULL;
    dict->size = 0;
    return dict;
}

void set_value(Dictionary *dict, const char *key, const char *value) {
    if (strcmp(key, "name") == 0) {
        free(dict->name);
        dict->size = strlen(value) + 1;
        dict->name = malloc(dict->size);
        strcpy(dict->name, value);
    }
}

const char* get_value(Dictionary *dict, const char *key) {
    if (strcmp(key, "name") == 0 && dict->name != NULL) {
        return dict->name;
    }
    return NULL;
}

void free_dictionary(Dictionary *dict) {
    free(dict->name);
    free(dict);
}

int main() {
    Dictionary *payload = create_dictionary();
    
    // Simulate loading payload
    set_value(payload, "name", "John Doe");
    
    const char* name_value = get_value(payload, "name");

    if (name_value) {
        printf("Name: %s\n", name_value);
    } else {
        printf("Name not found.\n");
    }

    free_dictionary(payload);

    return 0;
}