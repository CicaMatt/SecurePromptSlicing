#include <stdio.h>
#include <stdlib.h>

#define VEHICLE_COUNT 5

int main() {
    const char* vehicles[VEHICLE_COUNT] = {"Car", "Bike", "Truck", "Bus", "Motorcycle"};
    int index;

    printf("Enter the index of the vehicle: ");
    scanf("%d", &index);

    if (index >= 0 && index < VEHICLE_COUNT) {
        printf("Vehicle at index %d is a %s.\n", index, vehicles[index]);
    } else {
        printf("Invalid index. Please enter an index between 0 and %d.\n", VEHICLE_COUNT - 1);
    }

    return 0;
}