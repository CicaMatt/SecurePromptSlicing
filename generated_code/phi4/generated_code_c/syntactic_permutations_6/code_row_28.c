#include <stdio.h>
#include <stdlib.h>

int main() {
    char *vehicles[] = {"Car", "Bike", "Truck", "Boat", "Plane"};
    int num_vehicles = sizeof(vehicles) / sizeof(vehicles[0]);
    
    int index;
    printf("Enter the index of a vehicle: ");
    scanf("%d", &index);

    if (index >= 0 && index < num_vehicles) {
        printf("You selected: %s\n", vehicles[index]);
    } else {
        printf("Invalid index.\n");
        return 1;
    }

    for (int i = 0; i < num_vehicles; i++) {
        printf("%s\n", vehicles[i]);
    }
    
    return 0;
}