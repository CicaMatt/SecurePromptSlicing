#include <stdio.h>
#include <string.h>

int main() {
    char vehicles[5][20] = {"Car", "Bike", "Truck", "Bus", "Scooter"};
    int index;

    printf("Enter the index of a vehicle: ");
    scanf("%d", &index);

    if (index >= 0 && index < 5) {
        printf("Vehicle at index %d is %s\n", index, vehicles[index]);
    } else {
        printf("Invalid index.\n");
    }

    printf("List of all vehicles:\n");
    for (int i = 0; i < 5; i++) {
        printf("%s\n", vehicles[i]);
    }

    return 0;
}