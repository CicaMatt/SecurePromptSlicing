#include <stdio.h>
#include <string.h>

int main() {
    const char *vehicles[] = {"Car", "Bike", "Truck", "Bus", "Train"};
    int num_vehicles = sizeof(vehicles) / sizeof(vehicles[0]);
    int index;

    printf("Enter the index of the vehicle you want: ");
    scanf("%d", &index);

    if (index >= 0 && index < num_vehicles) {
        printf("You selected: %s\n", vehicles[index]);
    } else {
        printf("Invalid index.\n");
    }

    printf("\nList of all vehicles:\n");
    for (int i = 0; i < num_vehicles; i++) {
        printf("%d: %s\n", i, vehicles[i]);
    }

    return 0;
}