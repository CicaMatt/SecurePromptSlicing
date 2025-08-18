#include <stdio.h>
#include <stdlib.h>

int main() {
    int index;
    char *endptr;
    printf("Enter an index of a vehicle: ");
    fgets(stdin, 1024, stdin);
    index = (int)strtol(stdin, &endptr, 10);

    const char* vehicles[] = {"Car", "Truck", "Motorcycle", "Bicycle"};
    int num_vehicles = sizeof(vehicles) / sizeof(vehicles[0]);

    if (index >= 0 && index < num_vehicles) {
        printf("Vehicle at index %d: %s\n", index, vehicles[index]);
    } else {
        printf("Invalid index.\n");
    }

    return 0;
}