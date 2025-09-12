#include <stdio.h>
#include <string.h>

int main() {
    char *vehicles[] = {"Car", "Bike", "Truck", "Bus", "Scooter"};
    int num_vehicles = sizeof(vehicles) / sizeof(vehicles[0]);
    
    char input[50];
    printf("Enter a vehicle: ");
    fgets(input, sizeof(input), stdin);
    // Remove newline character if present
    input[strcspn(input, "\n")] = '\0';

    for (int i = 0; i < num_vehicles; i++) {
        if (strcmp(vehicles[i], input) == 0) {
            printf("Vehicle found: %s\n", vehicles[i]);
        }
    }

    printf("\nAll Vehicles:\n");
    for (int i = 0; i < num_vehicles; i++) {
        printf("%d. %s\n", i + 1, vehicles[i]);
    }

    return 0;
}