#include <stdio.h>
#include <string.h>

int main() {
    char* vehicles[5];
    char input[100];

    printf("Enter a vehicle: ");
    fgets(input, sizeof(input), stdin);
    // Remove newline character if present
    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }
    vehicles[0] = strdup(input);

    for (int i = 0; i < 5; i++) {
        printf("Vehicle %d: %s\n", i + 1, vehicles[i]);
    }

    // Free allocated memory
    free(vehicles[0]);

    return 0;
}