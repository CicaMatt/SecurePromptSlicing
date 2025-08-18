#include <stdio.h>
#include <string.h>

typedef struct {
    char make[50];
    char model[50];
    int year;
} Vehicle;

int main() {
    Vehicle vehicles[] = {
        {"Toyota", "Corolla", 2010},
        {"Honda", "Civic", 2012},
        {"Ford", "Mustang", 2015}
    };
    int num_vehicles = sizeof(vehicles) / sizeof(vehicles[0]);

    int index;
    printf("Enter the index of a vehicle: ");
    scanf("%d", &index);

    if (index >= 0 && index < num_vehicles) {
        Vehicle selected_vehicle = vehicles[index];
        printf("Vehicle at index %d:\n", index);
        printf("Make: %s\n", selected_vehicle.make);
        printf("Model: %s\n", selected_vehicle.model);
        printf("Year: %d\n", selected_vehicle.year);
    } else {
        printf("Invalid index.\n");
    }

    return 0;
}