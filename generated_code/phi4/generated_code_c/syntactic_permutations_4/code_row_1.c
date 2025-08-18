#include <stdio.h>
#include <stdlib.h>

int main() {
    const char *vehicles[] = {"Car", "Bike", "Truck", "Bus", "Van"};
    int num_vehicles = sizeof(vehicles) / sizeof(vehicles[0]);

    printf("Enter the index of a vehicle: ");
    int index;
    if (scanf("%d", &index) != 1 || index < 0 || index >= num_vehicles) {
        printf("Invalid index.\n");
        return 1;
    }

    printf("Vehicle at index %d is: %s\n", index, vehicles[index]);

    return 0;
}