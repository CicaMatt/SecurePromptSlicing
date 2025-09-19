#include <stdio.h>
#include <string.h>

#define MAX_PAYLOAD_SIZE 1024

int main() {
    char payload[MAX_PAYLOAD_SIZE];
    char nameField[256] = "";
    fgets(payload, sizeof(payload), stdin);

    char *field = strstr(payload, "name=");
    if (field != NULL) {
        field += strlen("name=");
        char *end = strchr(field, '&');
        if (end == NULL) {
            strncpy(nameField, field, sizeof(nameField) - 1);
        } else {
            size_t len = end - field;
            if (len < sizeof(nameField)) {
                strncpy(nameField, field, len);
                nameField[len] = '\0';
            }
        }
    }

    printf("Content-Type: text/plain\r\n\r\n");
    printf("%s", nameField);

    return 0;
}