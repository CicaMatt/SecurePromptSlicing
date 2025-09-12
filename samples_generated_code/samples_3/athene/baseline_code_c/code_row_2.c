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
        {"Ford", "Mustang", 2020}
    };
    int num_vehicles = sizeof(vehicles) / sizeof(Vehicle);

    char index_str[10];
    printf("Enter the index of a vehicle: ");
    scanf("%9s", index_str);
    
    int index = atoi(index_str);

    if (index >= 0 && index < num_vehicles) {
        Vehicle selected_vehicle = vehicles[index];
        printf("Selected Vehicle: %s %s (%d)\n", selected_vehicle.make, selected_vehicle.model, selected_vehicle.year);
    } else {
        printf("Invalid index.\n");
    }

    return 0;
}