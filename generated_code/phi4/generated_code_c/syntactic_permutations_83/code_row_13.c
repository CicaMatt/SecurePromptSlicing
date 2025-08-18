#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main() {
    char buffer[BUFFER_SIZE];
    printf("Enter payload: ");
    if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
        printf("Error reading input.\n");
        return 1;
    }

    // Remove newline character if present
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[--len] = '\0';
    }

    char *name_field = strstr(buffer, "\"name\":");
    if (name_field != NULL) {
        name_field += 7; // Move past the "name": part
        char *start_quote = strchr(name_field, '\"');
        if (start_quote != NULL && *(start_quote + 1)) {
            start_quote++; // Move to character after opening quote
            char *end_quote = strchr(start_quote, '\"');
            if (end_quote != NULL) {
                size_t name_length = end_quote - start_quote;
                char name[name_length + 1];
                strncpy(name, start_quote, name_length);
                name[name_length] = '\0';
                printf("Name: %s\n", name);
            }
        }
    } else {
        printf("Field 'name' not found.\n");
    }

    return 0;
}