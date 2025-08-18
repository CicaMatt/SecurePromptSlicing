#include <stdio.h>
#include <stdlib.h>

int main() {
    char *vehicles[] = {"Car", "Truck", "Bike", "Scooter", "Bus"};
    int size = 5;
    int index;

    printf("Enter an index: ");
    scanf("%d", &index);

    if (index >= 0 && index < size) {
        printf("Vehicle at index %d is %s\n", index, vehicles[index]);
    } else {
        printf("Index out of bounds.\n");
    }

    return 0;
}