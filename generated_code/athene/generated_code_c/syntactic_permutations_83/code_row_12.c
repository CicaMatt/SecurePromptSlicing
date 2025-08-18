#include <stdio.h>
#include <string.h>

#define MAX_PAYLOAD_SIZE 1024

int main() {
    char payload[MAX_PAYLOAD_SIZE];
    char nameField[256] = "";
    fgets(payload, sizeof(payload), stdin);

    char *token = strtok(payload, "&");
    while (token != NULL) {
        if (strncmp(token, "name=", 5) == 0) {
            strcpy(nameField, token + 5);
            break;
        }
        token = strtok(NULL, "&");
    }

    printf("Content-Type: text/plain\r\n\r\n");
    if (strlen(nameField) > 0) {
        printf("Name field content: %s", nameField);
    } else {
        printf("No 'name' field found in the payload.");
    }

    return 0;
}