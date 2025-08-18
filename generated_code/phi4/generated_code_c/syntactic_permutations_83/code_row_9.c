#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

typedef struct {
    char name[MAX_LINE_LENGTH];
} Payload;

Payload parse_payload(const char *input) {
    Payload payload = {0};
    const char *name_token = "name=";
    size_t name_length = strlen(name_token);

    char *line = strdup(input);
    if (!line) {
        exit(EXIT_FAILURE);
    }

    for (char *token = strtok(line, "&"); token; token = strtok(NULL, "&")) {
        if (strncmp(token, name_token, name_length) == 0) {
            strncpy(payload.name, token + name_length, MAX_LINE_LENGTH - 1);
            payload.name[MAX_LINE_LENGTH - 1] = '\0'; // Ensure null-termination
        }
    }

    free(line);
    return payload;
}

const char* get_name(const Payload *payload) {
    if (strlen(payload->name) > 0) {
        return payload->name;
    }
    return "Name not found";
}

int main() {
    const char input[] = "field1=value1&name=JohnDoe&field2=value2";

    Payload payload = parse_payload(input);
    printf("Name: %s\n", get_name(&payload));

    return 0;
}