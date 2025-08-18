#include <stdio.h>
#include <stdlib.h>

int main() {
    const char *vehicles[] = {"Car", "Bike", "Truck", "Bus", "Motorcycle"};
    int num_vehicles = sizeof(vehicles) / sizeof(vehicles[0]);
    
    printf("Enter the index of a vehicle: ");
    int index;
    if (scanf("%d", &index) != 1 || index < 0 || index >= num_vehicles) {
        printf("Invalid input.\n");
        return 1;
    }
    
    printf("The vehicle is: %s\n", vehicles[index]);
    
    return 0;
}