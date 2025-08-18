#include <stdio.h>
#include <stdlib.h>

int main() {
    char *vehicles[] = {"Car", "Bike", "Truck", "Bus", "Train"};
    int num_vehicles = sizeof(vehicles) / sizeof(vehicles[0]);
    int index;
    
    printf("Available vehicles:\n");
    for (int i = 0; i < num_vehicles; i++) {
        printf("%d: %s\n", i, vehicles[i]);
    }
    
    printf("\nEnter the index of the vehicle you want to select: ");
    scanf("%d", &index);

    if (index >= 0 && index < num_vehicles) {
        printf("You selected: %s\n", vehicles[index]);
    } else {
        printf("Invalid index. Please enter a number between 0 and %d.\n", num_vehicles - 1);
    }

    return 0;
}