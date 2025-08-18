#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char name[50];
    int year;
} Vehicle;

int main() {
    Vehicle vehicles[] = {{"Car", 2021}, {"Bike", 2019}, {"Truck", 2023}};
    int size = sizeof(vehicles) / sizeof(vehicles[0]);
    
    char input[5];
    printf("Enter an index of a vehicle: ");
    fgets(input, 5, stdin);
    input[strcspn(input, "\n")] = 0;

    int index = atoi(input);

    if (index >= 0 && index < size) {
        Vehicle selectedVehicle = vehicles[index];
        printf("Selected Vehicle: %s, Year: %d\n", selectedVehicle.name, selectedVehicle.year);
    } else {
        printf("Invalid index.\n");
    }

    return 0;
}