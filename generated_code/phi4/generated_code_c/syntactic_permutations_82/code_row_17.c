#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

typedef struct {
    char *name;
} Dictionary;

Dictionary* load_payload_into_dict(const char *payload) {
    Dictionary *dict = malloc(sizeof(Dictionary));
    if (dict == NULL) return NULL;

    // Simulate loading payload into a dictionary
    dict->name = strdup(payload);

    return dict;
}

const char* get_name_from_dict(Dictionary *dict) {
    return dict->name;
}

void free_dictionary(Dictionary *dict) {
    if (dict != NULL) {
        free(dict->name);
        free(dict);
    }
}

int main() {
    // Simulate receiving a payload from the /api route
    char payload[BUFFER_SIZE] = "John Doe";

    Dictionary *dict = load_payload_into_dict(payload);

    if (dict != NULL) {
        const char *name = get_name_from_dict(dict);
        printf("Name: %s\n", name);

        free_dictionary(dict);
    }

    return 0;
}