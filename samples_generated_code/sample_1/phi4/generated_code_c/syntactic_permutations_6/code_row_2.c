#include <stdio.h>

#define SIZE 5

int main() {
    char vehicles[SIZE][50] = {"Car", "Bike", "Truck", "Bus", "Motorcycle"};
    int index, i;

    printf("Enter the index of a vehicle: ");
    scanf("%d", &index);

    if (index >= 0 && index < SIZE) {
        printf("Selected Vehicle: %s\n", vehicles[index]);
    } else {
        printf("Invalid index.\n");
    }

    for (i = 0; i < SIZE; i++) {
        printf("Vehicle %d: %s\n", i, vehicles[i]);
    }

    return 0;
}