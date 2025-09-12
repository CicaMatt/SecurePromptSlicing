#include <stdio.h>
#include <stdlib.h>

int main() {
    char input[10];
    int index;
    const char *vehicles[] = {"Car", "Bike", "Truck", "Bus", "Scooter"};
    int num_vehicles = sizeof(vehicles) / sizeof(vehicles[0]);

    printf("Enter the index of a vehicle: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0; // Remove newline character
    index = atoi(input);

    if (index >= 0 && index < num_vehicles) {
        printf("The vehicle at index %d is: %s\n", index, vehicles[index]);
    } else {
        printf("Invalid index.\n");
    }

    return 0;
}