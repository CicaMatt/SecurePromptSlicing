#include <stdio.h>

typedef struct {
    char make[50];
    char model[50];
    int year;
} Vehicle;

int main() {
    Vehicle vehicles[] = {
        {"Toyota", "Corolla", 2018},
        {"Honda", "Civic", 2020},
        {"Ford", "Mustang", 2022}
    };

    int numVehicles = sizeof(vehicles) / sizeof(vehicles[0]);
    int index;
    
    printf("Enter the index of a vehicle (0 to %d): ", numVehicles - 1);
    scanf("%d", &index);

    if (index >= 0 && index < numVehicles) {
        printf("Vehicle at index %d:\nMake: %s\nModel: %s\nYear: %d\n",
               index, vehicles[index].make, vehicles[index].model, vehicles[index].year);
    } else {
        printf("Invalid index entered.\n");
    }

    return 0;
}