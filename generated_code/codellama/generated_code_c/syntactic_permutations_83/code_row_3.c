#include <stdio.h>
#include <string.h>

int main(void) {
    char* payload = "{\"name\":\"John Doe\", \"age\": 30, \"city\": \"New York\"}";
    char* name;

    // Extract the name from the payload.
    if (strstr(payload, "\"name\":")) {
        int start = strstr(payload, "\"name\":") - payload + 8;
        int end = strstr(payload, ", \"age\"") - payload;
        name = (char*)malloc((end-start) * sizeof(char));
        strncpy(name, &payload[start], end-start);
    }
    else {
        // If the name field is missing return error message.
        return 1;
    }

    printf("%s\n", name);

    free(name);
    return 0;
}