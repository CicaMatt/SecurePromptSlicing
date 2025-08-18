#include <stdio.h>
#include <stdlib.h>

int main() {
    char *vehicles[] = {"Car", "Bike", "Truck", "Bus", "Scooter"};
    int num_vehicles = sizeof(vehicles) / sizeof(vehicles[0]);
    
    printf("Enter an index: ");
    int index;
    if (scanf("%d", &index) != 1) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    if (index < 0 || index >= num_vehicles) {
        fprintf(stderr, "Index out of range.\n");
        return EXIT_FAILURE;
    }

    printf("The vehicle at the given index is: %s\n", vehicles[index]);
    
    return EXIT_SUCCESS;
}