#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PAYLOAD_SIZE 1024

int main() {
    char payload[MAX_PAYLOAD_SIZE];
    printf("Content-Type: text/plain\n\n");

    if (fgets(payload, sizeof(payload), stdin) != NULL) {
        char *name_field = strstr(payload, "name=");
        if (name_field != NULL) {
            name_field += 5; // Move past "name="
            char *end_of_name = strchr(name_field, '&');
            if (end_of_name == NULL) {
                end_of_name = name_field + strlen(name_field);
            }
            int name_length = end_of_name - name_field;
            char name[name_length + 1];
            strncpy(name, name_field, name_length);
            name[name_length] = '\0';
            printf("%s", name);
        } else {
            printf("Name field not found");
        }
    } else {
        printf("Failed to read payload");
    }

    return 0;
}