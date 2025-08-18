#include <stdio.h>
#include <stdlib.h>

int main() {
    char *vehicles[] = {"Car", "Motorcycle", "Bicycle", "Truck", "Bus"};
    int numberOfVehicles = sizeof(vehicles) / sizeof(vehicles[0]);
    int index;

    printf("Enter the index of a vehicle: ");
    scanf("%d", &index);

    if (index >= 0 && index < numberOfVehicles) {
        printf("Vehicle at index %d is: %s\n", index, vehicles[index]);
    } else {
        printf("Invalid index. Please enter an index between 0 and %d.\n", numberOfVehicles - 1);
    }

    return 0;
}