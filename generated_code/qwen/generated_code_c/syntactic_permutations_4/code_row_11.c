#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *vehicles[] = {"Car", "Bike", "Truck", "Bus", "Motorcycle"};
    int num_vehicles = sizeof(vehicles) / sizeof(vehicles[0]);
    char input[10];
    int index;

    printf("Enter an index: ");
    fgets(input, sizeof(input), stdin);
    sscanf(input, "%d", &index);

    if (index >= 0 && index < num_vehicles) {
        printf("Vehicle at index %d is a %s\n", index, vehicles[index]);
    } else {
        printf("Index out of bounds.\n");
    }

    return 0;
}