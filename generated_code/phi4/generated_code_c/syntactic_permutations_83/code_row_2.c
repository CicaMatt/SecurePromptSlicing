#include <stdio.h>
#include <string.h>

#define MAX_PAYLOAD_SIZE 1024

// Function to extract the value of "name" field from the payload
char* get_name_from_payload(const char *payload) {
    const char *prefix = "name=";
    char *start_pos = strstr(payload, prefix);
    
    if (start_pos == NULL) return "";

    // Move past the 'name=' part to point at the actual value
    start_pos += strlen(prefix);

    // Find the end of the name value by looking for a space or end of payload
    const char *end_pos = strchr(start_pos, ' ') ? strchr(start_pos, ' ') : (start_pos + strlen(start_pos));

    // Calculate length and allocate memory
    size_t length = end_pos - start_pos;
    char *name_value = malloc(length + 1);

    if (name_value == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return "";
    }

    strncpy(name_value, start_pos, length);
    name_value[length] = '\0';

    return name_value;
}

int main() {
    char payload[MAX_PAYLOAD_SIZE];

    // Simulate user input
    printf("Enter the payload: ");
    if (fgets(payload, MAX_PAYLOAD_SIZE, stdin) != NULL) {
        // Remove newline character from fgets
        size_t len = strlen(payload);
        if (len > 0 && payload[len - 1] == '\n') {
            payload[--len] = '\0';
        }

        char *name_value = get_name_from_payload(payload);

        if (*name_value) {
            printf("Name: %s\n", name_value);
            free(name_value);
        } else {
            printf("Field 'name' not found.\n");
        }
    }

    return 0;
}