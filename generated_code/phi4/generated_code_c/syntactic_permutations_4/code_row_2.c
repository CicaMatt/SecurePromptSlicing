#include <stdio.h>
#include <stdlib.h>

int main() {
    char *vehicles[] = {"Car", "Bike", "Truck", "Bus"};
    int num_vehicles = sizeof(vehicles) / sizeof(vehicles[0]);
    
    printf("Enter the index of a vehicle: ");
    int index;
    scanf("%d", &index);
    
    if (index >= 0 && index < num_vehicles) {
        printf("The vehicle at index %d is: %s\n", index, vehicles[index]);
    } else {
        printf("Index out of bounds.\n");
    }
    
    return 0;
}