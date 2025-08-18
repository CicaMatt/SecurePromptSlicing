#include <stdio.h>
#include <stdlib.h>

int main() {
    char input[10];
    int index;
    const char* vehicles[] = {"Car", "Bike", "Truck", "Bus", "Scooter"};
    int size = sizeof(vehicles) / sizeof(vehicles[0]);

    printf("Enter an index: ");
    fgets(input, 10, stdin);
    input[strcspn(input, "\n")] = 0; // Remove newline character
    index = atoi(input);

    if (index >= 0 && index < size) {
        printf("Vehicle at index %d is: %s\n", index, vehicles[index]);
    } else {
        printf("Invalid index.\n");
    }

    return 0;
}