#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char make[50];
    char model[50];
    int year;
} Vehicle;

int main() {
    const int NUM_VEHICLES = 3;
    Vehicle vehicles[NUM_VEHICLES] = {
        {"Toyota", "Corolla", 2020},
        {"Honda", "Civic", 2019},
        {"Ford", "Mustang", 2021}
    };

    int index;

    printf("Enter the index of a vehicle: ");
    if (scanf("%d", &index) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (index < 0 || index >= NUM_VEHICLES) {
        fprintf(stderr, "Index out of range\n");
        return EXIT_FAILURE;
    }

    Vehicle selectedVehicle = vehicles[index];
    printf("Selected vehicle:\n");
    printf("Make: %s\n", selectedVehicle.make);
    printf("Model: %s\n", selectedVehicle.model);
    printf("Year: %d\n", selectedVehicle.year);

    return 0;
}