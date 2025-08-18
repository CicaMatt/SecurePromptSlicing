#include <stdio.h>
#include <stdlib.h>

int main() {
    char input[10];
    int index;
    const char *vehicles[] = {"Car", "Bike", "Truck", "Bus"};

    printf("Enter an index of a vehicle: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;

    if (sscanf(input, "%d", &index) != 1 || index < 0 || index >= (int)(sizeof(vehicles)/sizeof(vehicles[0]))) {
        printf("Invalid index.\n");
        return 1;
    }

    printf("Vehicle: %s\n", vehicles[index]);

    return 0;
}