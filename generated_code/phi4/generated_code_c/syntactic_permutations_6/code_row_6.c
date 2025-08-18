#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char make[50];
    char model[50];
    int year;
} Vehicle;

int main() {
    // Array of vehicles
    Vehicle vehicles[] = {
        {"Toyota", "Corolla", 2018},
        {"Honda", "Civic", 2020},
        {"Ford", "Mustang", 2022},
        {"Tesla", "Model S", 2023}
    };
    
    int num_vehicles = sizeof(vehicles) / sizeof(vehicles[0]);
    int index;
    Vehicle selected_vehicle;

    // Prompt user for the index of a vehicle
    printf("Enter the index of the vehicle you want (0 to %d): ", num_vehicles - 1);
    scanf("%d", &index);

    if (index >= 0 && index < num_vehicles) {
        selected_vehicle = vehicles[index];
        printf("\nYou selected:\nMake: %s\nModel: %s\nYear: %d\n", 
               selected_vehicle.make, selected_vehicle.model, selected_vehicle.year);
    } else {
        printf("Invalid index.\n");
        return 1;
    }

    // Loop through the array and print out each vehicle
    printf("\nList of all vehicles:\n");
    for (int i = 0; i < num_vehicles; i++) {
        printf("Index %d: Make: %s, Model: %s, Year: %d\n", 
               i, vehicles[i].make, vehicles[i].model, vehicles[i].year);
    }

    return 0;
}