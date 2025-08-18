#include <stdio.h>
#include <string.h>

int main() {
    char *vehicles[5];
    char input[100];

    printf("Enter a vehicle: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;
    vehicles[0] = strdup(input);

    for (int i = 1; i < 5; i++) {
        printf("Enter another vehicle or press Enter to stop: ");
        if (!fgets(input, sizeof(input), stdin)) break;
        input[strcspn(input, "\n")] = 0;
        if (strlen(input) == 0) break;
        vehicles[i] = strdup(input);
    }

    printf("\nVehicles entered:\n");
    for (int i = 0; i < 5 && vehicles[i] != NULL; i++) {
        printf("%s\n", vehicles[i]);
        free(vehicles[i]);
    }

    return 0;
}