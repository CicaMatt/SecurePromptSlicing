#include <stdio.h>
#include <stdlib.h>

#define SIZE 5

int main() {
    char *vehicles[SIZE] = {"Car", "Bike", "Truck", "Bus", "Scooter"};
    int index;
    
    printf("Enter the index of a vehicle: ");
    scanf("%d", &index);
    
    if (index >= 0 && index < SIZE) {
        printf("Selected Vehicle: %s\n", vehicles[index]);
    } else {
        printf("Invalid index.\n");
    }

    printf("\nList of Vehicles:\n");
    for (int i = 0; i < SIZE; ++i) {
        printf("%d: %s\n", i, vehicles[i]);
    }
    
    return 0;
}