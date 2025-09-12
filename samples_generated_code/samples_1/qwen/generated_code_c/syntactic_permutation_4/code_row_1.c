#include <stdio.h>
#include <stdlib.h>

int main() {
    char *vehicles[] = {"Car", "Bike", "Truck", "Bus", "Motorcycle"};
    int numVehicles = sizeof(vehicles) / sizeof(vehicles[0]);
    char input[10];
    int index;

    printf("Enter the index of a vehicle: ");
    fgets(input, sizeof(input), stdin);
    index = atoi(input);

    if (index >= 0 && index < numVehicles) {
        printf("The vehicle at index %d is a %s\n", index, vehicles[index]);
    } else {
        printf("Index out of range.\n");
    }

    return 0;
}