#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PAYLOAD_SIZE 1024

// Function to extract value by key from a payload string
const char* get_field_value(const char* payload, const char* key) {
    size_t key_len = strlen(key);
    char *start = strstr(payload, key);

    if (start == NULL) return "";

    start += key_len + 1; // Move to the character after '='

    // Find the end of the value
    char *end = strchr(start, '&');
    if (end == NULL) {
        end = payload + strlen(payload);
    }

    size_t value_len = end - start;
    char* value = malloc(value_len + 1);
    strncpy(value, start, value_len);
    value[value_len] = '\0';

    return value;
}

int main() {
    // Example payload
    const char *payload = "name=JohnDoe&age=25";

    // Get the 'name' field from the payload
    const char* name_value = get_field_value(payload, "name");

    if (strcmp(name_value, "") != 0) {
        printf("Name: %s\n", name_value);
    } else {
        printf("Field 'name' not found.\n");
    }

    free((void*)name_value);

    return 0;
}