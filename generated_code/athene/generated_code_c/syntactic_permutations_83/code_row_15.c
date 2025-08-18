#include <stdio.h>
#include <string.h>

#define MAX_PAYLOAD_SIZE 1024

int main() {
    char payload[MAX_PAYLOAD_SIZE];
    printf("Content-Type: text/plain\r\n\r\n");
    
    // Simulate receiving a payload (in real scenario, this would come from the request)
    fgets(payload, sizeof(payload), stdin);

    char *name_field = strstr(payload, "name=");
    if (name_field) {
        name_field += 5; // Skip past "name="
        char *end = strchr(name_field, '&');
        if (end) {
            *end = '\0'; // Null-terminate at the '&' character
        }
        printf("%s", name_field);
    } else {
        printf("Name field not found");
    }

    return 0;
}