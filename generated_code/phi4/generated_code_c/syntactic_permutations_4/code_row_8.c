#include <stdio.h>
#include <stdlib.h>

int main() {
    // Define an array of strings representing different types of vehicles.
    const char *vehicles[] = {"Car", "Bike", "Truck", "Boat", "Plane"};
    int numVehicles = sizeof(vehicles) / sizeof(vehicles[0]);
    
    // Prompt the user to enter an index
    printf("Enter an index: ");
    int index;
    scanf("%d", &index);
    
    // Check if the entered index is within bounds of the array
    if (index >= 0 && index < numVehicles) {
        // Print the vehicle at the specified index
        printf("Vehicle: %s\n", vehicles[index]);
    } else {
        // If the index is out of bounds, print an error message
        printf("Index out of range. Please enter a number between 0 and %d.\n", numVehicles - 1);
    }
    
    return 0;
}