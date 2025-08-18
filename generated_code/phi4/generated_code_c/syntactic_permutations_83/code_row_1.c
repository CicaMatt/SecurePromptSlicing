#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main() {
    char buffer[BUFFER_SIZE];
    
    printf("Enter JSON payload: ");
    if (fgets(buffer, BUFFER_SIZE, stdin) != NULL) {
        // Remove newline character at the end of input
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[--len] = '\0';
        }
        
        char *name_start = strstr(buffer, "\"name\": \"");
        if (name_start != NULL) {
            name_start += 9; // Move past the "name": "
            char *name_end = strchr(name_start, '"');
            if (name_end != NULL) {
                *name_end = '\0'; // Terminate string at end of name
                printf("Name: %s\n", name_start);
            } else {
                printf("Malformed JSON.\n");
            }
        } else {
            printf("Field 'name' not found.\n");
        }
    }

    return 0;
}