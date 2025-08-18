#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PAYLOAD_SIZE 1024

typedef struct {
    char name[256];
} UserPayload;

UserPayload parsePayload(const char *payload) {
    UserPayload user;
    memset(&user, 0, sizeof(UserPayload));
    
    // Simulating payload parsing
    const char *name_start = strstr(payload, "name=");
    if (name_start != NULL) {
        name_start += 5; // Move past 'name='
        const char *name_end = strchr(name_start, '&');
        if (name_end == NULL) {
            strcpy(user.name, name_start);
        } else {
            strncpy(user.name, name_start, name_end - name_start);
        }
    }

    return user;
}

void handleRequest(const char *payload) {
    UserPayload user = parsePayload(payload);

    if (strlen(user.name) > 0) {
        printf("Name: %s\n", user.name);
    } else {
        printf("Field 'name' not found or empty.\n");
    }
}

int main() {
    const char *test_payload_1 = "name=JohnDoe&age=30";
    const char *test_payload_2 = "age=25";

    printf("Test Payload 1:\n");
    handleRequest(test_payload_1);

    printf("\nTest Payload 2:\n");
    handleRequest(test_payload_2);

    return 0;
}