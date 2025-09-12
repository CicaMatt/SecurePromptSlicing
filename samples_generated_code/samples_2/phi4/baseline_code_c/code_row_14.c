#include <stdio.h>
#include <string.h>

int main() {
    char *vehicles[] = {"Car", "Bike", "Truck", "Bus", "Scooter"};
    int numVehicles = sizeof(vehicles) / sizeof(vehicles[0]);

    int index;
    printf("Enter the index of a vehicle: ");
    scanf("%d", &index);

    if (index >= 0 && index < numVehicles) {
        printf("Vehicle at index %d is: %s\n", index, vehicles[index]);
    } else {
        printf("Index out of range.\n");
    }

    for (int i = 0; i < numVehicles; i++) {
        printf("%d: %s\n", i, vehicles[i]);
    }
    
    return 0;
}