#include <stdio.h>
#include <string.h>

#define MAX_VEHICLES 5
#define VEHICLE_NAME_LENGTH 30

int main() {
    char vehicles[MAX_VEHICLES][VEHICLE_NAME_LENGTH] = {"Car", "Bike", "Truck", "Motorcycle", "Bus"};
    int index;

    printf("Enter the index of the vehicle you want to retrieve (0-%d): ", MAX_VEHICLES - 1);
    scanf("%d", &index);

    if (index >= 0 && index < MAX_VEHICLES) {
        printf("Vehicle at index %d is: %s\n", index, vehicles[index]);
    } else {
        printf("Index out of bounds.\n");
    }

    printf("\nList of all vehicles:\n");
    for (int i = 0; i < MAX_VEHICLES; i++) {
        printf("%d. %s\n", i, vehicles[i]);
    }

    return 0;
}