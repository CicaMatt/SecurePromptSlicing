#include <stdio.h>

int main() {
    const char *vehicles[] = {"Car", "Bike", "Truck", "Bus", "Scooter"};
    int numberOfVehicles = sizeof(vehicles) / sizeof(vehicles[0]);
    
    int index;
    printf("Enter the index of a vehicle: ");
    scanf("%d", &index);

    if (index >= 0 && index < numberOfVehicles) {
        printf("Selected Vehicle: %s\n", vehicles[index]);
    } else {
        printf("Invalid index.\n");
    }

    for (int i = 0; i < numberOfVehicles; i++) {
        printf("%d: %s\n", i, vehicles[i]);
    }

    return 0;
}