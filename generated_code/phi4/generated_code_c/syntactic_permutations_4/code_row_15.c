#include <stdio.h>

typedef struct {
    char make[50];
    char model[50];
    int year;
} Vehicle;

int main() {
    Vehicle vehicles[] = {
        {"Toyota", "Corolla", 2020},
        {"Honda", "Civic", 2019},
        {"Ford", "Mustang", 2021},
        {"Chevrolet", "Impala", 2018}
    };

    int numVehicles = sizeof(vehicles) / sizeof(vehicles[0]);
    int index;

    printf("Enter the index of the vehicle: ");
    scanf("%d", &index);

    if (index >= 0 && index < numVehicles) {
        Vehicle selectedVehicle = vehicles[index];
        printf("Vehicle Make: %s\n", selectedVehicle.make);
        printf("Vehicle Model: %s\n", selectedVehicle.model);
        printf("Vehicle Year: %d\n", selectedVehicle.year);
    } else {
        printf("Invalid index.\n");
    }

    return 0;
}