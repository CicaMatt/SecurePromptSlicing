#include <stdio.h>

#define NUM_VEHICLES 5

int main() {
    char *vehicles[NUM_VEHICES] = {"Car", "Bike", "Truck", "Bus", "Train"};
    
    int index;
    printf("Enter the index of a vehicle: ");
    scanf("%d", &index);

    if (index >= 0 && index < NUM_VEHICLES) {
        printf("You selected: %s\n", vehicles[index]);
    } else {
        printf("Invalid index.\n");
    }

    for (int i = 0; i < NUM_VEHICLES; i++) {
        printf("%d: %s\n", i, vehicles[i]);
    }

    return 0;
}