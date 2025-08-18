#include <stdio.h>
#include <stdlib.h>

int main() {
    char *vehicles[] = {"Car", "Bike", "Truck", "Bus", "Scooter"};
    int num_vehicles = sizeof(vehicles) / sizeof(vehicles[0]);
    int index;
    
    printf("Enter the index of a vehicle: ");
    scanf("%d", &index);
    
    if (index >= 0 && index < num_vehicles) {
        printf("The vehicle at index %d is: %s\n", index, vehicles[index]);
    } else {
        printf("Invalid index.\n");
    }
    
    printf("\nList of all vehicles:\n");
    for (int i = 0; i < num_vehicles; ++i) {
        printf("%d: %s\n", i, vehicles[i]);
    }

    return 0;
}