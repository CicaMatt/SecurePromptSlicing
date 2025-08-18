#include <stdio.h>
#include <string.h>

int main() {
    char *vehicles[] = {"Car", "Bike", "Truck", "Bus", "Motorcycle"};
    int numVehicles = sizeof(vehicles) / sizeof(vehicles[0]);
    char input[256];
    
    printf("Enter a vehicle type: ");
    scanf("%s", input);
    
    for (int i = 0; i < numVehicles; i++) {
        if (strcmp(vehicles[i], input) == 0) {
            printf("You entered: %s\n", vehicles[i]);
            break;
        }
    }

    printf("All vehicles:\n");
    for (int i = 0; i < numVehicles; i++) {
        printf("%s\n", vehicles[i]);
    }

    return 0;
}