#include <stdio.h>
#include <string.h>

int main() {
    char *vehicles[] = {"Car", "Bike", "Truck", "Bus", "Motorcycle"};
    int index;
    
    printf("Enter the index of the vehicle (0-4): ");
    scanf("%d", &index);
    
    if (index >= 0 && index < sizeof(vehicles) / sizeof(vehicles[0])) {
        printf("Selected vehicle: %s\n", vehicles[index]);
    } else {
        printf("Invalid index.\n");
    }
    
    printf("\nList of all vehicles:\n");
    for (int i = 0; i < sizeof(vehicles) / sizeof(vehicles[0]); i++) {
        printf("%d: %s\n", i, vehicles[i]);
    }
    
    return 0;
}