#include <stdio.h>
#include <stdlib.h>

#define MAX_VEHICLES 10

int main() {
    char *vehicles[MAX_VEHILES] = {
        "Car",
        "Bike",
        "Truck",
        "Bus",
        "Plane",
        "Boat",
        "Train",
        "Helicopter",
        "Scooter",
        "Motorcycle"
    };

    int index;
    printf("Enter the index of the vehicle you want to retrieve: ");
    scanf("%d", &index);

    if (index >= 0 && index < MAX_VEHICLES) {
        printf("Selected Vehicle: %s\n", vehicles[index]);
    } else {
        printf("Invalid index!\n");
    }

    printf("\nList of Vehicles:\n");
    for (int i = 0; i < MAX_VEHICLES; i++) {
        printf("%d: %s\n", i, vehicles[i]);
    }

    return 0;
}