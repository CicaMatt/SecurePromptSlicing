#include <stdio.h>
#include <stdlib.h>

int main() {
    char* vehicles[] = {"Car", "Bike", "Truck", "Bus", "Motorcycle"};
    int num_vehicles = sizeof(vehicles) / sizeof(vehicles[0]);
    
    printf("Enter the index of a vehicle: ");
    int index;
    if (scanf("%d", &index) != 1 || index < 0 || index >= num_vehicles) {
        printf("Invalid input. Please enter an integer between 0 and %d.\n", num_vehicles - 1);
        return 1;
    }
    
    printf("The vehicle at index %d is: %s\n", index, vehicles[index]);
    return 0;
}