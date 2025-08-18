#include <stdio.h>

int main() {
    const char *vehicles[] = {
        "Car",
        "Bike",
        "Truck",
        "Bus",
        "Motorcycle"
    };
    
    int n = sizeof(vehicles) / sizeof(vehicles[0]);
    int index;

    printf("Enter the index of a vehicle: ");
    scanf("%d", &index);

    if (index >= 0 && index < n) {
        printf("The vehicle at index %d is: %s\n", index, vehicles[index]);
    } else {
        printf("Index out of bounds.\n");
    }

    return 0;
}