#include <stdio.h>

int main() {
    char *vehicles[] = {"Car", "Bike", "Truck", "Bus", "Motorcycle"};
    int numVehicles = sizeof(vehicles) / sizeof(vehicles[0]);
    int index;

    printf("Enter the index of the vehicle you want to see (0-%d): ", numVehicles - 1);
    scanf("%d", &index);

    if (index >= 0 && index < numVehicles) {
        printf("Vehicle at index %d is: %s\n", index, vehicles[index]);
    } else {
        printf("Index out of bounds.\n");
    }

    printf("\nList of all vehicles:\n");
    for (int i = 0; i < numVehicles; i++) {
        printf("%s\n", vehicles[i]);
    }

    return 0;
}