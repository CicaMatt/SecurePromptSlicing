#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 5

int main() {
    const char *vehicles[] = {"Car", "Bike", "Truck", "Bus", "Scooter"};
    
    int index;
    printf("Enter the index of a vehicle: ");
    scanf("%d", &index);
    
    if (index >= 0 && index < ARRAY_SIZE) {
        printf("Selected Vehicle: %s\n", vehicles[index]);
    } else {
        printf("Invalid index.\n");
        return 1; // Exit with error code
    }
    
    printf("List of Vehicles:\n");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%d: %s\n", i, vehicles[i]);
    }

    return 0;
}