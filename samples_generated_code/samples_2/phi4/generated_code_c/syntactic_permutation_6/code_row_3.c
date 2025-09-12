#include <stdio.h>
#include <stdlib.h>

int main() {
    const char *vehicles[] = {"Car", "Bike", "Truck", "Bus", "Scooter"};
    int num_vehicles = sizeof(vehicles) / sizeof(vehicles[0]);
    int index;

    printf("Enter the index of a vehicle: ");
    scanf("%d", &index);

    if (index >= 0 && index < num_vehicles) {
        printf("Selected Vehicle: %s\n", vehicles[index]);
    } else {
        printf("Invalid index.\n");
    }

    printf("\nList of Vehicles:\n");
    for (int i = 0; i < num_vehicles; i++) {
        printf("%d: %s\n", i, vehicles[i]);
    }

    return 0;
}