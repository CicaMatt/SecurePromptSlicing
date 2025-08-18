#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char make[50];
    char model[50];
    int year;
} Vehicle;

int main() {
    Vehicle vehicles[] = {
        {"Toyota", "Corolla", 2020},
        {"Ford", "Mustang", 2019},
        {"Honda", "Civic", 2021},
        {"Chevrolet", "Malibu", 2018}
    };
    
    int numVehicles = sizeof(vehicles) / sizeof(Vehicle);
    int index;
    
    printf("Enter the index of a vehicle: ");
    if (scanf("%d", &index) != 1 || index < 0 || index >= numVehicles) {
        printf("Invalid index.\n");
        return 1;
    }
    
    Vehicle selectedVehicle = vehicles[index];
    
    printf("Selected Vehicle:\n");
    printf("Make: %s\n", selectedVehicle.make);
    printf("Model: %s\n", selectedVehicle.model);
    printf("Year: %d\n", selectedVehicle.year);

    return 0;
}