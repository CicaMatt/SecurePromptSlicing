#include <stdio.h>
#include <string.h>

int main() {
    const char *vehicles[] = {"Car", "Bike", "Truck", "Scooter", "Bus"};
    int numVehicles = sizeof(vehicles) / sizeof(vehicles[0]);
    
    printf("Select a vehicle by index (0-%d): ", numVehicles - 1);
    int index;
    scanf("%d", &index);

    if (index >= 0 && index < numVehicles) {
        printf("You selected: %s\n", vehicles[index]);

        for (int i = 0; i < numVehicles; i++) {
            printf("Vehicle at index %d is: %s\n", i, vehicles[i]);
        }
    } else {
        printf("Invalid index!\n");
    }

    return 0;
}