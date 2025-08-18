#include <stdio.h>
#include <stdlib.h>

struct Vehicle {
    char name[50];
};

int main() {
    struct Vehicle vehicles[] = {
        {"Car"},
        {"Bike"},
        {"Truck"},
        {"Bus"}
    };
    
    int numVehicles = sizeof(vehicles) / sizeof(vehicles[0]);
    int index;

    printf("Enter the index of a vehicle: ");
    if (scanf("%d", &index) != 1 || index < 0 || index >= numVehicles) {
        fprintf(stderr, "Invalid index entered.\n");
        return EXIT_FAILURE;
    }

    printf("The vehicle at the given index is: %s\n", vehicles[index].name);
    
    return EXIT_SUCCESS;
}