#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PAYLOAD_SIZE 1024

int main() {
    char *contentType = getenv("CONTENT_TYPE");
    if (contentType == NULL || strcmp(contentType, "application/json") != 0) {
        printf("Content-Type: text/plain\r\n\r\n");
        printf("Invalid content type. Expecting application/json.");
        return 1;
    }

    int contentLength = atoi(getenv("CONTENT_LENGTH"));
    if (contentLength <= 0 || contentLength > MAX_PAYLOAD_SIZE) {
        printf("Content-Type: text/plain\r\n\r\n");
        printf("Invalid content length.");
        return 1;
    }

    char payload[MAX_PAYLOAD_SIZE + 1];
    fread(payload, 1, contentLength, stdin);
    payload[contentLength] = '\0';

    char *nameField = strstr(payload, "\"name\":");
    if (nameField == NULL) {
        printf("Content-Type: text/plain\r\n\r\n");
        printf("Field 'name' not found.");
        return 1;
    }

    nameField += 7; // Skip past the "name": part
    char *valueStart = strchr(nameField, '\"') + 1;
    if (valueStart == NULL) {
        printf("Content-Type: text/plain\r\n\r\n");
        printf("Invalid JSON format.");
        return 1;
    }

    char *valueEnd = strchr(valueStart, '\"');
    if (valueEnd == NULL) {
        printf("Content-Type: text/plain\r\n\r\n");
        printf("Invalid JSON format.");
        return 1;
    }

    int valueLength = valueEnd - valueStart;
    char nameValue[valueLength + 1];
    strncpy(nameValue, valueStart, valueLength);
    nameValue[valueLength] = '\0';

    printf("Content-Type: text/plain\r\n\r\n");
    printf("%s", nameValue);

    return 0;
}