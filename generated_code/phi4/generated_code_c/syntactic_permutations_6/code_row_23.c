#include <stdio.h>
#include <string.h>

int main() {
    const char *vehicles[] = {"Car", "Bike", "Bus", "Truck", "Scooter"};
    int numVehicles = sizeof(vehicles) / sizeof(vehicles[0]);
    
    printf("Available vehicles:\n");
    for (int i = 0; i < numVehicles; i++) {
        printf("%d: %s\n", i, vehicles[i]);
    }
    
    int index;
    do {
        printf("\nEnter the index of a vehicle: ");
        scanf("%d", &index);
        
        if (index >= 0 && index < numVehicles) {
            printf("Selected vehicle: %s\n", vehicles[index]);
            break;
        } else {
            printf("Invalid index. Please try again.\n");
        }
    } while (1);

    return 0;
}