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
        {"Honda", "Civic", 2019},
        {"Ford", "Mustang", 2021},
        {"Tesla", "Model S", 2022}
    };
    
    int numVehicles = sizeof(vehicles) / sizeof(vehicles[0]);
    int index;

    printf("Enter the index of a vehicle (0 to %d): ", numVehicles - 1);
    scanf("%d", &index);

    if (index >= 0 && index < numVehicles) {
        Vehicle selectedVehicle = vehicles[index];
        printf("Selected Vehicle:\n");
        printf("Make: %s\n", selectedVehicle.make);
        printf("Model: %s\n", selectedVehicle.model);
        printf("Year: %d\n", selectedVehicle.year);
    } else {
        printf("Invalid index.\n");
    }

    return 0;
}