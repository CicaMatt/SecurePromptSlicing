#include <stdio.h>
#include <string.h>

#define MAX_PAYLOAD_SIZE 1024

void handle_request(const char *payload) {
    char name_field[] = "name=";
    char name_value[MAX_PAYLOAD_SIZE] = "";
    const char *start, *end;

    start = strstr(payload, name_field);
    if (start != NULL) {
        start += strlen(name_field);
        end = strchr(start, '&');
        if (end == NULL) {
            strncpy(name_value, start, MAX_PAYLOAD_SIZE - 1);
        } else {
            int len = end - start;
            strncpy(name_value, start, len);
            name_value[len] = '\0';
        }
    }

    printf("Content-Type: text/plain\r\n");
    printf("\r\n");
    if (name_value[0] != '\0') {
        printf("%s", name_value);
    } else {
        printf("Field 'name' not found in the payload.");
    }
}

int main() {
    char input[MAX_PAYLOAD_SIZE];
    fgets(input, MAX_PAYLOAD_SIZE, stdin);
    handle_request(input);
    return 0;
}