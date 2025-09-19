#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PAYLOAD_SIZE 256

typedef struct {
    char *name;
} Dictionary;

void parse_payload(const char *payload, Dictionary *dict) {
    const char *prefix = "name=";
    if (strncmp(payload, prefix, strlen(prefix)) == 0) {
        dict->name = strdup(payload + strlen(prefix));
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s payload\n", argv[0]);
        return EXIT_FAILURE;
    }

    Dictionary dict = {NULL};

    parse_payload(argv[1], &dict);

    if (dict.name != NULL) {
        printf("%s\n", dict.name);
        free(dict.name);
    } else {
        fprintf(stderr, "Name not found in payload\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}