#include <stdio.h>

int main() {
    const char *vehicles[] = {"Car", "Bike", "Truck", "Motorcycle", "Bus"};
    int numVehicles = sizeof(vehicles) / sizeof(vehicles[0]);
    int index;

    printf("Enter the index of a vehicle: ");
    scanf("%d", &index);

    if (index >= 0 && index < numVehicles) {
        printf("The selected vehicle is: %s\n", vehicles[index]);
    } else {
        printf("Invalid index. Please enter a number between 0 and %d.\n", numVehicles - 1);
    }

    return 0;
}