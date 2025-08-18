#include <stdio.h>
#include <string.h>

int main() {
    char *vehicles[] = {"Car", "Bike", "Truck", "Bus"};
    int numVehicles = sizeof(vehicles) / sizeof(vehicles[0]);
    
    printf("Enter a vehicle type: ");
    char userInput[100];
    scanf("%99s", userInput);
    
    printf("You entered: %s\n", userInput);
    
    printf("List of vehicles:\n");
    for (int i = 0; i < numVehicles; i++) {
        printf("%s\n", vehicles[i]);
    }
    
    return 0;
}