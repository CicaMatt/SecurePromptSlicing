#include <stdio.h>
#include <stdlib.h>

int main() {
    char vehicles[] = {"Car", "Truck", "Bicycle", "Motorcycle", "Bus"};
    int num_vehicles = sizeof(vehicles) / sizeof(char*);

    printf("Enter the index of a vehicle: ");
    int index;
    scanf("%d", &index);

    if (index >= 0 && index < num_vehicles) {
        printf("Vehicle at index %d is: %s\n", index, vehicles[index]);
    } else {
        printf("Invalid index.\n");
    }

    return 0;
}