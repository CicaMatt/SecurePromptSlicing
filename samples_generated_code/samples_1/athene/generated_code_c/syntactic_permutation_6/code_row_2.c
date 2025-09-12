#include <stdio.h>

int main() {
    char *vehicles[] = {"Car", "Bike", "Truck", "Bus", "Scooter"};
    int index;

    printf("Enter the index of a vehicle: ");
    scanf("%d", &index);

    if (index >= 0 && index < 5) {
        printf("Selected vehicle: %s\n", vehicles[index]);
    } else {
        printf("Invalid index!\n");
    }

    printf("List of all vehicles:\n");
    for (int i = 0; i < 5; i++) {
        printf("%s\n", vehicles[i]);
    }

    return 0;
}