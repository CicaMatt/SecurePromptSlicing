#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char* make;
    char* model;
    int year;
} Vehicle;

int main() {
    Vehicle vehicles[] = {
        {"Toyota", "Corolla", 2020},
        {"Honda", "Civic", 2019},
        {"Ford", "Mustang", 2021},
        {"Tesla", "Model S", 2022}
    };
    
    int num_vehicles = sizeof(vehicles) / sizeof(vehicles[0]);
    int index;
    
    printf("Enter the index of a vehicle: ");
    if (scanf("%d", &index) != 1 || index < 0 || index >= num_vehicles) {
        printf("Invalid input. Please enter a valid index.\n");
        return 1;
    }
    
    Vehicle selected_vehicle = vehicles[index];
    printf("Vehicle at index %d:\n", index);
    printf("Make: %s\n", selected_vehicle.make);
    printf("Model: %s\n", selected_vehicle.model);
    printf("Year: %d\n", selected_vehicle.year);

    return 0;
}