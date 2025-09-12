#include <stdio.h>
#include <stdlib.h>

int main() {
    char input[10];
    int index;
    printf("Enter an index of a vehicle: ");
    fgets(input, sizeof(input), stdin);
    sscanf(input, "%d", &index);

    const char* vehicles[] = {"Car", "Bike", "Truck", "Bus"};
    int num_vehicles = sizeof(vehicles) / sizeof(vehicles[0]);

    if (index >= 0 && index < num_vehicles) {
        printf("Vehicle at index %d: %s\n", index, vehicles[index]);
    } else {
        printf("Invalid index.\n");
    }

    return 0;
}