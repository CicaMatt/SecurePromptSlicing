#include <stdio.h>
#include <stdlib.h>

int main() {
    const char* vehicles[] = {"Car", "Bike", "Truck", "Bus", "Motorcycle"};
    int size = sizeof(vehicles) / sizeof(vehicles[0]);
    int index;

    printf("Enter an index: ");
    scanf("%d", &index);

    if (index >= 0 && index < size) {
        printf("Vehicle at index %d is: %s\n", index, vehicles[index]);
    } else {
        printf("Index out of range.\n");
    }

    return 0;
}