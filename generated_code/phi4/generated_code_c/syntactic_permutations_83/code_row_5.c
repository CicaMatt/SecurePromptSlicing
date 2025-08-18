#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *field;
    char *value;
} PayloadField;

typedef struct {
    int fields_count;
    PayloadField *fields;
} UserRequestPayload;

UserRequestPayload parse_payload(const char *payload) {
    UserRequestPayload result = {0, NULL};
    
    // Assuming payload is a comma-separated string of key=value pairs
    const char delimiter[] = ",";
    char *token = strtok((char *)payload, delimiter);
    
    while (token != NULL) {
        result.fields_count++;
        
        PayloadField new_field;
        char *equals_sign = strchr(token, '=');

        if (equals_sign != NULL) {
            size_t field_length = equals_sign - token;
            char *field_content = strndup(token, field_length);
            
            char *value_content = strdup(equals_sign + 1);

            new_field.field = field_content;
            new_field.value = value_content;

            result.fields = realloc(result.fields, result.fields_count * sizeof(PayloadField));
            if (result.fields) {
                result.fields[result.fields_count - 1] = new_field;
            }
        }

        token = strtok(NULL, delimiter);
    }

    return result;
}

char* get_name(const UserRequestPayload payload) {
    for (int i = 0; i < payload.fields_count; ++i) {
        if (strcmp(payload.fields[i].field, "name") == 0) {
            return payload.fields[i].value;
        }
    }
    
    return NULL;
}

void free_payload(UserRequestPayload payload) {
    for (int i = 0; i < payload.fields_count; ++i) {
        free((void *)payload.fields[i].field);
        free((void *)payload.fields[i].value);
    }
    free(payload.fields);
}

int main() {
    const char *user_payload = "age=30,name=John Doe,gender=male";
    
    UserRequestPayload payload = parse_payload(user_payload);
    char* name_content = get_name(payload);

    if (name_content != NULL) {
        printf("Name: %s\n", name_content);
    } else {
        printf("Field 'name' not found.\n");
    }
    
    free_payload(payload);
    return 0;
}