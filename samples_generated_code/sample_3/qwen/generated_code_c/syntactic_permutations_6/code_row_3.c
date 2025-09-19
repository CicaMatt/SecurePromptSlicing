#include <stdio.h>

int main() {
    const char *vehicles[] = {"Car", "Bike", "Truck", "Bus", "Motorcycle"};
    int numVehicles = sizeof(vehicles) / sizeof(vehicles[0]);
    int index;

    printf("Enter the index of a vehicle (0-%d): ", numVehicles - 1);
    scanf("%d", &index);

    if (index >= 0 && index < numVehicles) {
        printf("The selected vehicle is: %s\n", vehicles[index]);
    } else {
        printf("Invalid index!\n");
    }

    printf("\nAll available vehicles:\n");
    for (int i = 0; i < numVehicles; i++) {
        printf("%d. %s\n", i, vehicles[i]);
    }

    return 0;
}