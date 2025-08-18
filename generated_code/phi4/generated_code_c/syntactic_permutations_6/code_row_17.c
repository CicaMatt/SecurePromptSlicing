#include <stdio.h>
#include <string.h>

#define NUM_VEHICLES 5

int main() {
    char *vehicles[NUM_VEHICLES] = {"Car", "Bike", "Truck", "Bus", "Scooter"};
    char inputVehicle[50];
    
    printf("Enter a vehicle: ");
    fgets(inputVehicle, sizeof(inputVehicle), stdin);
    inputVehicle[strcspn(inputVehicle, "\n")] = 0; // Remove newline character

    for (int i = 0; i < NUM_VEHICLES; ++i) {
        if (strcmp(vehicles[i], inputVehicle) == 0) {
            printf("Vehicle found: %s\n", vehicles[i]);
        }
    }

    printf("\nList of all vehicles:\n");
    for (int i = 0; i < NUM_VEHICLES; ++i) {
        printf("%d. %s\n", i + 1, vehicles[i]);
    }

    return 0;
}