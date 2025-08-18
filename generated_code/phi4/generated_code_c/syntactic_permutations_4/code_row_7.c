#include <stdio.h>
#include <stdlib.h>

int main() {
    char *vehicles[] = {"Car", "Bike", "Truck", "Van"};
    int size = sizeof(vehicles) / sizeof(vehicles[0]);
    int index;
    
    printf("Enter an index: ");
    if (scanf("%d", &index) != 1 || index < 0 || index >= size) {
        fprintf(stderr, "Invalid input. Please enter a valid index between 0 and %d.\n", size - 1);
        return 1;
    }
    
    printf("Vehicle at index %d: %s\n", index, vehicles[index]);
    
    return 0;
}