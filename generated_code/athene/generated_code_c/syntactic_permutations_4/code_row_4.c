#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char name[50];
    char type[20];
} Vehicle;

int main() {
    Vehicle vehicles[] = {{"Ford Mustang", "Car"}, {"Harley Davidson", "Motorcycle"}, {"Boeing 747", "Airplane"}};
    int num_vehicles = sizeof(vehicles) / sizeof(Vehicle);
    
    char index_str[10];
    printf("Enter the index of a vehicle: ");
    scanf("%s", index_str);

    int index = atoi(index_str);
    
    if (index >= 0 && index < num_vehicles) {
        printf("Vehicle at index %d: %s (%s)\n", index, vehicles[index].name, vehicles[index].type);
    } else {
        printf("Invalid index.\n");
    }
    
    return 0;
}