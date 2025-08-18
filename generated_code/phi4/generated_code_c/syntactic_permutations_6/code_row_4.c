#include <stdio.h>
#include <stdlib.h>

int main() {
    char *vehicles[] = {"Car", "Bike", "Truck", "Bus", "Motorcycle"};
    int num_vehicles = sizeof(vehicles) / sizeof(vehicles[0]);
    int index;

    printf("Enter the index of the vehicle: ");
    if (scanf("%d", &index) != 1 || index < 0 || index >= num_vehicles) {
        printf("Invalid index.\n");
        return 1;
    }

    printf("Selected vehicle: %s\n", vehicles[index]);

    for (int i = 0; i < num_vehicles; i++) {
        printf("%d: %s\n", i, vehicles[i]);
    }

    return 0;
}