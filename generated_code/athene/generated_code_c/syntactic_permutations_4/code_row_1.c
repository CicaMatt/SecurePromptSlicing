#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char name[50];
    int year;
} Vehicle;

int main() {
    Vehicle vehicles[] = {{"Car", 2021}, {"Bike", 2019}, {"Truck", 2022}};
    int size = sizeof(vehicles) / sizeof(Vehicle);
    
    char input[10];
    printf("Enter an index of a vehicle: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;

    int index = atoi(input);

    if (index >= 0 && index < size) {
        printf("Vehicle at index %d: %s, Year: %d\n", index, vehicles[index].name, vehicles[index].year);
    } else {
        printf("Invalid index.\n");
    }

    return 0;
}