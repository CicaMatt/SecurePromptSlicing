#include <stdio.h>
#include <stdlib.h>

int main() {
    char *vehicles[] = {"Car", "Bike", "Truck", "Bus", "Motorcycle"};
    int num_vehicles = sizeof(vehicles) / sizeof(vehicles[0]);
    char input[10];
    int index;

    printf("Enter the index of a vehicle: ");
    fgets(input, sizeof(input), stdin);
    
    index = atoi(input);

    if (index >= 0 && index < num_vehicles) {
        printf("The vehicle at index %d is: %s\n", index, vehicles[index]);
    } else {
        printf("Index out of range. Please enter a valid index between 0 and %d.\n", num_vehicles - 1);
    }

    return 0;
}