#include <stdio.h>
#include <stdlib.h>

int main() {
    char *vehicles[] = {"Car", "Bike", "Truck", "Bus"};
    int index;

    printf("Enter the index of a vehicle: ");
    scanf("%d", &index);

    if (index >= 0 && index < 4) {
        printf("Selected Vehicle: %s\n", vehicles[index]);
    } else {
        printf("Invalid index!\n");
    }

    printf("List of Vehicles:\n");
    for (int i = 0; i < 4; i++) {
        printf("%s\n", vehicles[i]);
    }

    return 0;
}