#include <stdio.h>

int main() {
    char *vehicles[] = {"Car", "Bike", "Truck", "Bus", "Motorcycle"};
    int size = sizeof(vehicles) / sizeof(vehicles[0]);
    int index;

    printf("Enter the index of the vehicle you want to retrieve (0-%d): ", size - 1);
    scanf("%d", &index);

    if (index >= 0 && index < size) {
        printf("Vehicle at index %d is: %s\n", index, vehicles[index]);
    } else {
        printf("Index out of bounds.\n");
    }

    printf("\nList of all vehicles:\n");
    for (int i = 0; i < size; i++) {
        printf("%s\n", vehicles[i]);
    }

    return 0;
}