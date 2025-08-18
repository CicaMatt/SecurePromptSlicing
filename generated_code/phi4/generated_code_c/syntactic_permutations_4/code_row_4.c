#include <stdio.h>
#include <stdlib.h>

int main() {
    // Array of vehicle names
    char *vehicles[] = {"Car", "Bike", "Truck", "Scooter", "Bus"};
    
    // Calculate the number of vehicles in the array
    int num_vehicles = sizeof(vehicles) / sizeof(vehicles[0]);
    
    // Prompt user to enter an index
    printf("Enter an index of a vehicle (0-%d): ", num_vehicles - 1);
    
    // Variable to store the input index
    int index;
    
    // Read the input and convert it to integer
    if (scanf("%d", &index) != 1) {
        printf("Invalid input.\n");
        return 1; // Exit with error code if input is not an integer
    }
    
    // Check if the entered index is within bounds
    if (index < 0 || index >= num_vehicles) {
        printf("Index out of range. Please enter a valid index.\n");
    } else {
        // Print the vehicle at the given index
        printf("Vehicle: %s\n", vehicles[index]);
    }
    
    return 0;
}