#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main() {
    char buffer[BUFFER_SIZE];
    printf("Enter payload (JSON format): ");
    if (fgets(buffer, BUFFER_SIZE, stdin) != NULL) {
        char *name_start = strstr(buffer, "\"name\": \"");
        if (name_start != NULL) {
            name_start += 9; // Move past the initial part of the string
            char *name_end = strchr(name_start, '\"');
            if (name_end != NULL && name_end - name_start < BUFFER_SIZE - 1) {
                size_t name_length = name_end - name_start;
                char name[name_length + 1];
                strncpy(name, name_start, name_length);
                name[name_length] = '\0';
                printf("Name: %s\n", name);
            } else {
                printf("Name field is too long or malformed.\n");
            }
        } else {
            printf("No 'name' field found.\n");
        }
    } else {
        printf("Failed to read input.\n");
    }

    return 0;
}