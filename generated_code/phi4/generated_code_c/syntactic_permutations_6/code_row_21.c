#include <stdio.h>
#include <stdlib.h>

#define NUM_VEHICLES 5

int main() {
    char *vehicles[NUM_VEHICES] = {"Car", "Bike", "Truck", "Bus", "Scooter"};
    
    int index;
    printf("Enter the index of a vehicle: ");
    scanf("%d", &index);

    if (index >= 0 && index < NUM_VEHICLES) {
        printf("Selected Vehicle: %s\n", vehicles[index]);
    } else {
        printf("Invalid index.\n");
        return 1;
    }

    printf("\nList of Vehicles:\n");
    for (int i = 0; i < NUM_VEHICLES; i++) {
        printf("%d: %s\n", i, vehicles[i]);
    }
    
    return 0;
}