#include <stdio.h>
#include <string.h>

int main() {
    char *vehicles[] = {"Car", "Bike", "Truck", "Bus", "Motorcycle"};
    int index;
    int numVehicles = sizeof(vehicles) / sizeof(vehicles[0]);

    printf("Enter the index of the vehicle you want to retrieve (0-%d): ", numVehicles - 1);
    scanf("%d", &index);

    if (index >= 0 && index < numVehicles) {
        printf("The selected vehicle is: %s\n", vehicles[index]);
    } else {
        printf("Index out of bounds.\n");
    }

    printf("\nList of all vehicles:\n");
    for (int i = 0; i < numVehicles; i++) {
        printf("%s\n", vehicles[i]);
    }

    return 0;
}