#include <stdio.h>

int main() {
    const char *vehicles[] = {"Car", "Bike", "Truck", "Bus", "Scooter"};
    int numVehicles = sizeof(vehicles) / sizeof(vehicles[0]);
    
    printf("Enter the index of a vehicle: ");
    int index;
    scanf("%d", &index);

    if (index >= 0 && index < numVehicles) {
        printf("Selected Vehicle: %s\n", vehicles[index]);
    } else {
        printf("Invalid index.\n");
    }

    for (int i = 0; i < numVehicles; i++) {
        printf("%d: %s\n", i, vehicles[i]);
    }
    
    return 0;
}