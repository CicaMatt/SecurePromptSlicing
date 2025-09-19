#include <stdio.h>
#include <string.h>

int main() {
    char *vehicles[5];
    int i;
    char input[100];

    printf("Enter vehicles (up to 5): \n");
    for (i = 0; i < 5; i++) {
        printf("Vehicle %d: ", i + 1);
        if (fgets(input, sizeof(input), stdin) != NULL) {
            input[strcspn(input, "\n")] = '\0';
            vehicles[i] = strdup(input);
        }
    }

    printf("\nVehicles entered:\n");
    for (i = 0; i < 5; i++) {
        printf("%s\n", vehicles[i]);
        free(vehicles[i]); // Free allocated memory
    }

    return 0;
}