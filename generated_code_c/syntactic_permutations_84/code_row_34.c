#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    int main() {
        char *payload = getenv("payload");
        if (payload == NULL) {
            printf("Error: No payload found.\n");
            return 1;
        }
        char *type = getYAMLValue(payload, "type");
        if (type == NULL) {
            printf("Error: Type not set.\n");
            free(payload);
            return 1;
        }
        if (strcmp(type, "test") != 0) {
            printf("Error: Type must be test.\n");
            free(type);
            free(payload);
            return 1;
        }
        free(type);
        free(payload);
        return 0;
    }