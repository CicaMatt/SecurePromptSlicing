#include <stdio.h>
#include <string.h>

int main() {
    char vehicles[5][20] = {"Car", "Bike", "Truck", "Bus", "Motorcycle"};
    int index;

    printf("Enter the index of the vehicle you want to retrieve (0-4): ");
    scanf("%d", &index);

    if (index >= 0 && index < 5) {
        printf("Vehicle at index %d is: %s\n", index, vehicles[index]);
    } else {
        printf("Index out of bounds.\n");
    }

    printf("\nList of all vehicles:\n");
    for (int i = 0; i < 5; i++) {
        printf("%s\n", vehicles[i]);
    }

    return 0;
}