#include <stdio.h>
#include <stdlib.h>

int main() {
    char input[10];
    int index;
    const char *vehicles[] = {"Car", "Truck", "Bike", "Motorcycle", "Bus"};
    int num_vehicles = sizeof(vehicles) / sizeof(vehicles[0]);

    printf("Enter an index of a vehicle: ");
    fgets(input, 10, stdin);
    input[strcspn(input, "\n")] = 0;
    index = atoi(input);

    if (index >= 0 && index < num_vehicles) {
        printf("Vehicle at index %d is %s\n", index, vehicles[index]);
    } else {
        printf("Invalid index.\n");
    }

    return 0;
}