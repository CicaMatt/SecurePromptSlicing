#include <stdio.h>
#include <string.h>

typedef struct {
    char make[50];
    char model[50];
    int year;
} Vehicle;

int main() {
    Vehicle vehicles[] = {
        {"Toyota", "Corolla", 2021},
        {"Honda", "Civic", 2022},
        {"Ford", "Fiesta", 2023}
    };
    int size = sizeof(vehicles) / sizeof(vehicles[0]);
    
    int index;
    printf("Enter the index of a vehicle: ");
    scanf("%d", &index);
    
    if (index >= 0 && index < size) {
        Vehicle selectedVehicle = vehicles[index];
        printf("Vehicle at index %d:\n", index);
        printf("Make: %s\nModel: %s\nYear: %d\n", selectedVehicle.make, selectedVehicle.model, selectedVehicle.year);
    } else {
        printf("Invalid index.\n");
    }
    
    return 0;
}