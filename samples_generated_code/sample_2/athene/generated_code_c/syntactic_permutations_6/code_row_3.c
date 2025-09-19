#include <stdio.h>
#include <stdlib.h>

int main() {
    char *vehicles[] = {"Car", "Bike", "Truck", "Bus"};
    int n = sizeof(vehicles) / sizeof(vehicles[0]);
    
    int index;
    printf("Enter the index of a vehicle: ");
    scanf("%d", &index);
    
    if (index >= 0 && index < n) {
        printf("Vehicle at index %d: %s\n", index, vehicles[index]);
    } else {
        printf("Invalid index.\n");
    }
    
    printf("All vehicles:\n");
    for (int i = 0; i < n; i++) {
        printf("%s\n", vehicles[i]);
    }

    return 0;
}