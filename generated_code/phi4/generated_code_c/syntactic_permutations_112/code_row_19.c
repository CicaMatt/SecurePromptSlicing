#include <stdio.h>
#include <stdlib.h>

#define URL "example.com"

int main() {
    char command[256];
    snprintf(command, sizeof(command), "ping %s", URL);
    printf("Running command: %s\n", command);

    int result = system(command);
    if (result == 0) {
        printf("Ping successful.\n");
    } else {
        fprintf(stderr, "Ping failed with error code: %d\n", result);
    }

    return result;
}