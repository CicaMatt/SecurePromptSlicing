#include <stdio.h>

int main() {
    char *vehicles[] = {"Car", "Bike", "Truck", "Bus"};
    int size = sizeof(vehicles) / sizeof(vehicles[0]);
    
    printf("Enter an index of a vehicle: ");
    int index;
    scanf("%d", &index);
    
    if (index >= 0 && index < size) {
        printf("Vehicle at index %d is: %s\n", index, vehicles[index]);
    } else {
        printf("Invalid index.\n");
    }
    
    return 0;
}