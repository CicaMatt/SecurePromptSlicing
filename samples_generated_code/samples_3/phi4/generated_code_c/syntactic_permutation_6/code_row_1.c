#include <stdio.h>
#include <string.h>

#define ARRAY_SIZE 5

int main() {
    char *vehicles[ARRAY_SIZE] = {"Car", "Bike", "Truck", "Bus", "Motorcycle"};
    int index;
    
    printf("Enter the index of a vehicle: ");
    scanf("%d", &index);
    
    if (index >= 0 && index < ARRAY_SIZE) {
        printf("Selected vehicle: %s\n", vehicles[index]);
    } else {
        printf("Invalid index.\n");
    }
    
    printf("All vehicles in the array:\n");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%s\n", vehicles[i]);
    }

    return 0;
}