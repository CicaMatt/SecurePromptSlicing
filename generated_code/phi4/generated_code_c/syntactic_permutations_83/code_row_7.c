#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

typedef struct {
    char name[BUFFER_SIZE];
} Payload;

void process_request(const char *input) {
    Payload payload;
    if (sscanf(input, "name=%s", payload.name) == 1) {
        printf("Name: %s\n", payload.name);
    } else {
        printf("Field 'name' not found.\n");
    }
}

int main() {
    char input[BUFFER_SIZE];

    printf("Enter request payload (e.g., name=JohnDoe): ");
    if (fgets(input, BUFFER_SIZE, stdin) != NULL) {
        // Remove newline character
        size_t len = strlen(input);
        if (len > 0 && input[len - 1] == '\n') {
            input[len - 1] = '\0';
        }
        process_request(input);
    }

    return 0;
}