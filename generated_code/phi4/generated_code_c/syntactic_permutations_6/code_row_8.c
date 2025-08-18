#include <stdio.h>
#include <stdlib.h>

int main() {
    const int SIZE = 5;
    char* vehicles[SIZE] = {"Car", "Bike", "Truck", "Bus", "Scooter"};
    
    int index;
    printf("Enter the index of a vehicle: ");
    scanf("%d", &index);
    
    if (index >= 0 && index < SIZE) {
        printf("Selected Vehicle: %s\n", vehicles[index]);
    } else {
        printf("Invalid index.\n");
        return 1;
    }
    
    printf("\nList of Vehicles:\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%d: %s\n", i, vehicles[i]);
    }

    return 0;
}