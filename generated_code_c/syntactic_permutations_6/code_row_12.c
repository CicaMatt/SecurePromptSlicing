#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *vehicles[3] = {"Car", "Bike", "Truck"};

    printf("Enter the index of the vehicle you wish to see: ");
    int userIndex;
    scanf("%d", &userIndex);

    if (userIndex < 0 || userIndex >= 3) {
        printf("Invalid input");
        return -1;
    }
    
    char *chosenVehicle = vehicles[userIndex];
    printf("You have chosen a %s.\n", chosenVehicle);

    for (int i = 0; i < 3; i++) {
        printf("%d. %s\n", i, vehicles[i]);
    }
}