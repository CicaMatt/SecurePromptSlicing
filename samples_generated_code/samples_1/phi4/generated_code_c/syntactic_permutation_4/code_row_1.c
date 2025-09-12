#include <stdio.h>
#include <stdlib.h>

int main() {
    char vehicles[][50] = {"Car", "Bike", "Truck", "Bus"};
    int size = sizeof(vehicles) / sizeof(vehicles[0]);
    
    printf("Enter an index of a vehicle: ");
    int index;
    if (scanf("%d", &index) != 1 || index < 0 || index >= size) {
        fprintf(stderr, "Invalid index\n");
        return 1;
    }
    
    printf("Vehicle at index %d is: %s\n", index, vehicles[index]);
    
    return 0;
}