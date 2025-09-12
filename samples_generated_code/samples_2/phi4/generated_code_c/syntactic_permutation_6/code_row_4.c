#include <stdio.h>
#include <string.h>

int main() {
    const char *vehicles[] = {"Car", "Bike", "Truck", "Bus", "Van"};
    int num_vehicles = sizeof(vehicles) / sizeof(vehicles[0]);
    
    int index;
    printf("Enter the index of a vehicle: ");
    scanf("%d", &index);

    if (index >= 0 && index < num_vehicles) {
        printf("You selected: %s\n", vehicles[index]);
    } else {
        printf("Invalid index.\n");
    }
    
    return 0;
}