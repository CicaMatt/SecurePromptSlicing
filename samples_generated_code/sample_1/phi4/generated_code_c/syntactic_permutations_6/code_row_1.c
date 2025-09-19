#include <stdio.h>
#include <string.h>

int main() {
    const int SIZE = 5;
    char *vehicles[SIZE] = {"Car", "Bike", "Truck", "Boat", "Plane"};
    
    char userVehicle[50];
    printf("Enter a vehicle: ");
    scanf("%49s", userVehicle);
    
    printf("You entered: %s\n", userVehicle);

    for (int i = 0; i < SIZE; ++i) {
        printf("Vehicle %d: %s\n", i + 1, vehicles[i]);
    }

    return 0;
}