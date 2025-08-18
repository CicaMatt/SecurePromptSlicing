#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PAYLOAD_SIZE 1024

char* find_name_field(const char* payload) {
    const char* name_prefix = "name=";
    size_t prefix_len = strlen(name_prefix);
    char* start = strstr(payload, name_prefix);

    if (start == NULL) {
        return NULL;
    }

    start += prefix_len;
    char* end = strchr(start, '&');

    if (end == NULL) {
        end = start + strlen(start);
    }

    size_t field_length = end - start;
    char* result = malloc(field_length + 1);
    strncpy(result, start, field_length);
    result[field_length] = '\0';

    return result;
}

int main() {
    const char* payload = "username=john&name=doe&age=30";
    char* name_field = find_name_field(payload);

    if (name_field != NULL) {
        printf("Name field content: %s\n", name_field);
        free(name_field);
    } else {
        printf("Name field not found.\n");
    }

    return 0;
}