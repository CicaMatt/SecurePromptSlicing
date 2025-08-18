#include <stdio.h>
#include <stdlib.h>

int main() {
    const char* vehicles[] = {"Car", "Bike", "Truck", "Bus", "Motorcycle"};
    int numVehicles = sizeof(vehicles) / sizeof(vehicles[0]);
    
    printf("Enter the index of a vehicle (0 to %d): ", numVehicles - 1);
    char input[10];
    fgets(input, sizeof(input), stdin);

    int index = atoi(input);

    if (index >= 0 && index < numVehicles) {
        printf("Vehicle at index %d is: %s\n", index, vehicles[index]);
    } else {
        printf("Invalid index. Please enter a number between 0 and %d.\n", numVehicles - 1);
    }

    return 0;
}