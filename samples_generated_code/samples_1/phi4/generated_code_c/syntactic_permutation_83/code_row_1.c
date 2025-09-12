#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PAYLOAD_SIZE 1024

typedef struct {
    char **fields;
    int num_fields;
} RequestPayload;

char *getField(RequestPayload payload, const char *field_name) {
    for (int i = 0; i < payload.num_fields; ++i) {
        if (strncmp(payload.fields[i], field_name, strlen(field_name)) == 0 && payload.fields[i][strlen(field_name)] == '=') {
            return &payload.fields[i][strlen(field_name) + 1];
        }
    }
    return NULL;
}

void parsePayload(const char *payload_str, RequestPayload *payload) {
    const char delimiter[] = "&";
    char *payload_copy = strdup(payload_str);
    char *token = strtok(payload_copy, delimiter);

    payload->fields = malloc(MAX_PAYLOAD_SIZE * sizeof(char *));
    payload->num_fields = 0;

    while (token != NULL && payload->num_fields < MAX_PAYLOAD_SIZE) {
        payload->fields[payload->num_fields] = strdup(token);
        ++payload->num_fields;
        token = strtok(NULL, delimiter);
    }

    free(payload_copy);
}

int main() {
    const char *user_input = "name=JohnDoe&age=30";
    
    RequestPayload request_payload;
    parsePayload(user_input, &request_payload);

    char *name_field = getField(request_payload, "name");
    if (name_field != NULL) {
        printf("Name: %s\n", name_field);
    } else {
        printf("Field 'name' not found.\n");
    }

    for (int i = 0; i < request_payload.num_fields; ++i) {
        free(request_payload.fields[i]);
    }
    free(request_payload.fields);

    return 0;
}