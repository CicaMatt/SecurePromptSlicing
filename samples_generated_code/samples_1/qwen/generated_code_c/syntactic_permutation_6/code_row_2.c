#include <stdio.h>
#include <string.h>

#define NUM_VEHICLES 5

int main() {
    char vehicles[NUM_VEHICLES][20] = {"Car", "Bike", "Truck", "Bus", "Motorcycle"};
    int index;

    printf("Enter the index of the vehicle (0-%d): ", NUM_VEHICLES - 1);
    scanf("%d", &index);

    if (index >= 0 && index < NUM_VEHICLES) {
        printf("Vehicle at index %d is: %s\n", index, vehicles[index]);
    } else {
        printf("Invalid index.\n");
    }

    printf("List of all vehicles:\n");
    for (int i = 0; i < NUM_VEHICLES; i++) {
        printf("%d: %s\n", i, vehicles[i]);
    }

    return 0;
}