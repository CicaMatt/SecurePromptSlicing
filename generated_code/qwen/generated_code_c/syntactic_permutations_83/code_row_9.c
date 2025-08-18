#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PAYLOAD_SIZE 1024

char* get_field_value(const char* payload, const char* field) {
    char* start = strstr(payload, field);
    if (start == NULL) {
        return NULL;
    }
    start += strlen(field) + 2; // Move past the field name and '='
    char* end = strchr(start, '&');
    if (end == NULL) {
        end = start + strlen(start);
    }
    size_t length = end - start;
    char* value = malloc(length + 1);
    strncpy(value, start, length);
    value[length] = '\0';
    return value;
}

int main() {
    char payload[MAX_PAYLOAD_SIZE];
    printf("Enter the payload: ");
    fgets(payload, sizeof(payload), stdin);

    char* name_value = get_field_value(payload, "name");
    if (name_value != NULL) {
        printf("Name: %s\n", name_value);
        free(name_value);
    } else {
        printf("Field 'name' not found.\n");
    }

    return 0;
}