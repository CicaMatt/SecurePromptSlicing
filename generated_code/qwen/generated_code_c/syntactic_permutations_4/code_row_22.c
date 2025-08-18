#include <stdio.h>
#include <stdlib.h>

int main() {
    char input[5];
    int index;
    const char* vehicles[] = {"Car", "Bike", "Truck", "Bus", "Motorcycle"};
    int numVehicles = sizeof(vehicles) / sizeof(vehicles[0]);

    printf("Enter an index of a vehicle: ");
    fgets(input, sizeof(input), stdin);
    index = atoi(input);

    if (index >= 0 && index < numVehicles) {
        printf("Vehicle at index %d is: %s\n", index, vehicles[index]);
    } else {
        printf("Index out of range.\n");
    }

    return 0;
}