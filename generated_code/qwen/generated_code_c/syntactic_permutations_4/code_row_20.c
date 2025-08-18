#include <stdio.h>
#include <stdlib.h>

int main() {
    char input[10];
    int index;
    const char* vehicles[] = {"Car", "Bike", "Truck", "Motorcycle", "Bus"};
    int numVehicles = sizeof(vehicles) / sizeof(vehicles[0]);

    printf("Enter an index of a vehicle: ");
    fgets(input, sizeof(input), stdin);
    index = atoi(input);

    if (index >= 0 && index < numVehicles) {
        printf("Vehicle at index %d is: %s\n", index, vehicles[index]);
    } else {
        printf("Invalid index.\n");
    }

    return 0;
}