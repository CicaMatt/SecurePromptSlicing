#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char* make;
    char* model;
    int year;
} Vehicle;

const Vehicle vehicles[] = {
    {"Toyota", "Corolla", 2020},
    {"Honda", "Civic", 2019},
    {"Ford", "Mustang", 2021},
    {"Chevrolet", "Malibu", 2018}
};

int main() {
    int index;
    
    printf("Enter the index of a vehicle: ");
    if (scanf("%d", &index) != 1 || index < 0 || index >= sizeof(vehicles) / sizeof(vehicles[0])) {
        fprintf(stderr, "Invalid input. Please enter a valid index.\n");
        return EXIT_FAILURE;
    }
    
    Vehicle selectedVehicle = vehicles[index];
    
    printf("Selected Vehicle:\n");
    printf("Make: %s\n", selectedVehicle.make);
    printf("Model: %s\n", selectedVehicle.model);
    printf("Year: %d\n", selectedVehicle.year);
    
    return EXIT_SUCCESS;
}