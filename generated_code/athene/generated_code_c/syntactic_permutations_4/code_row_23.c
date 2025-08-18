#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *make;
    char *model;
    int year;
} Vehicle;

int main() {
    Vehicle vehicles[] = {
        {"Toyota", "Corolla", 2015},
        {"Honda", "Civic", 2017},
        {"Ford", "Fiesta", 2018}
    };
    int size = sizeof(vehicles) / sizeof(Vehicle);
    
    char indexStr[10];
    printf("Enter the index of a vehicle: ");
    fgets(indexStr, 10, stdin);
    indexStr[strcspn(indexStr, "\n")] = 0;

    int index = atoi(indexStr);

    if (index >= 0 && index < size) {
        Vehicle selectedVehicle = vehicles[index];
        printf("Selected Vehicle: %s %s (%d)\n", selectedVehicle.make, selectedVehicle.model, selectedVehicle.year);
    } else {
        printf("Invalid index.\n");
    }

    return 0;
}