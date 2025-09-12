#include <stdio.h>
#include <stdlib.h>

int main() {
    char *vehicles[] = {"Car", "Bike", "Truck", "Bus", "Train"};
    int numVehicles = sizeof(vehicles) / sizeof(vehicles[0]);

    int index;
    printf("Enter the index of a vehicle: ");
    scanf("%d", &index);

    if (index >= 0 && index < numVehicles) {
        printf("Vehicle at index %d is: %s\n", index, vehicles[index]);
    } else {
        printf("Invalid index.\n");
        return 1;
    }

    for (int i = 0; i < numVehicles; i++) {
        printf("%s\n", vehicles[i]);
    }

    return 0;
}