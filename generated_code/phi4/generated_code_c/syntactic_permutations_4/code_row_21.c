#include <stdio.h>
#include <stdlib.h>

int main() {
    const char *vehicles[] = {"Car", "Bike", "Truck", "Bus"};
    int size = sizeof(vehicles) / sizeof(vehicles[0]);
    
    printf("Enter the index of a vehicle: ");
    int index;
    if (scanf("%d", &index) != 1 || index < 0 || index >= size) {
        fprintf(stderr, "Invalid index.\n");
        return EXIT_FAILURE;
    }
    
    printf("You selected: %s\n", vehicles[index]);
    return EXIT_SUCCESS;
}