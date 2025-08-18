#include <stdio.h>
#include <string.h>

int main() {
    char vehicles[5][20] = {"Car", "Bike", "Truck", "Bus", "Motorcycle"};
    int index;

    printf("Enter the index of the vehicle (0-4): ");
    scanf("%d", &index);

    if (index >= 0 && index < 5) {
        printf("Selected Vehicle: %s\n", vehicles[index]);
    } else {
        printf("Invalid index!\n");
    }

    printf("\nList of all vehicles:\n");
    for (int i = 0; i < 5; i++) {
        printf("%d. %s\n", i, vehicles[i]);
    }

    return 0;
}