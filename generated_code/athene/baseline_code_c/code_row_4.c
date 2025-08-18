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
        {"Ford", "Fiesta", 2017}
    };
    int size = sizeof(vehicles) / sizeof(Vehicle);
    
    char input[10];
    printf("Enter an index of a vehicle: ");
    fgets(input, 10, stdin);
    input[strcspn(input, "\n")] = 0;

    int index = atoi(input);

    if (index >= 0 && index < size) {
        Vehicle selectedVehicle = vehicles[index];
        printf("Selected Vehicle: %s %s %d\n", selectedVehicle.make, selectedVehicle.model, selectedVehicle.year);
    } else {
        printf("Invalid index.\n");
    }

    return 0;
}