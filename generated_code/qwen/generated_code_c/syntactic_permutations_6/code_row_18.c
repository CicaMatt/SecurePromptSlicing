#include <stdio.h>

int main() {
    char *vehicles[] = {"Car", "Bike", "Truck", "Bus", "Motorcycle"};
    int index, numVehicles;

    numVehicles = sizeof(vehicles) / sizeof(vehicles[0]);

    printf("Enter the index of the vehicle (0 to %d): ", numVehicles - 1);
    scanf("%d", &index);

    if (index >= 0 && index < numVehicles) {
        printf("The selected vehicle is: %s\n", vehicles[index]);
    } else {
        printf("Invalid index!\n");
    }

    printf("\nList of all vehicles:\n");
    for (int i = 0; i < numVehicles; i++) {
        printf("%d. %s\n", i, vehicles[i]);
    }

    return 0;
}