#include <stdio.h>
#include <string.h>

#define MAX_PAYLOAD_SIZE 1024

void handle_request(const char *payload) {
    char name_field[] = "name=";
    char *value_start;
    size_t value_length;

    if (strstr(payload, name_field)) {
        value_start = strstr(payload, name_field) + strlen(name_field);
        value_length = strcspn(value_start, "&");
        printf("Content-Type: text/plain\r\n\r\n");
        printf("%.*s", (int)value_length, value_start);
    } else {
        printf("Content-Type: text/plain\r\n\r\n");
        printf("Field 'name' not found in payload.");
    }
}

int main() {
    char buffer[MAX_PAYLOAD_SIZE];
    FILE *fp = fopen("/dev/stdin", "r");
    if (fp == NULL) {
        return 1;
    }

    fgets(buffer, MAX_PAYLOAD_SIZE, fp);
    fclose(fp);

    handle_request(buffer);

    return 0;
}