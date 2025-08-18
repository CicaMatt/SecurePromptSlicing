#include <stdio.h>
#include <stdlib.h>

int main() {
    char *vehicles[] = {"Car", "Truck", "Motorcycle", "Bicycle"};
    int num_vehicles = sizeof(vehicles) / sizeof(vehicles[0]);
    
    printf("Enter the index of a vehicle: ");
    int index;
    if (scanf("%d", &index) != 1 || index < 0 || index >= num_vehicles) {
        fprintf(stderr, "Invalid index.\n");
        return EXIT_FAILURE;
    }

    printf("The vehicle at index %d is: %s\n", index, vehicles[index]);

    return EXIT_SUCCESS;
}