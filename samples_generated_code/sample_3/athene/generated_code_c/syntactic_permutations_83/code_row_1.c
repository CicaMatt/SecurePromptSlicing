#include <stdio.h>
#include <string.h>

#define MAX_PAYLOAD_SIZE 1024

int main() {
    char payload[MAX_PAYLOAD_SIZE] = "";
    printf("Content-Type: text/plain\r\n\r\n");
    
    // Simulate receiving a payload from the user (for simplicity, we read it from stdin)
    if (fgets(payload, sizeof(payload), stdin) == NULL) {
        printf("No input received.\n");
        return 1;
    }

    char *name_field = strstr(payload, "name=");
    if (name_field != NULL) {
        // Extract the value of 'name' field
        name_field += 5; // Skip "name="
        char *end_of_value = strchr(name_field, '&');
        if (end_of_value != NULL) {
            *end_of_value = '\0'; // Null-terminate at the '&' character
        }
        printf("Name: %s\n", name_field);
    } else {
        printf("Field 'name' not found.\n");
    }

    return 0;
}