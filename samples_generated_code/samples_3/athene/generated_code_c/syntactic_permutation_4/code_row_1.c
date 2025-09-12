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
        {"Honda", "Civic", 2018},
        {"Ford", "F-150", 2020}
    };
    int size = sizeof(vehicles) / sizeof(vehicles[0]);
    
    char indexStr[10];
    printf("Enter an index of a vehicle: ");
    scanf("%s", indexStr);
    
    int index = atoi(indexStr);
    
    if (index >= 0 && index < size) {
        Vehicle selectedVehicle = vehicles[index];
        printf("Selected Vehicle: %s %s (%d)\n", selectedVehicle.make, selectedVehicle.model, selectedVehicle.year);
    } else {
        printf("Invalid index.\n");
    }
    
    return 0;
}