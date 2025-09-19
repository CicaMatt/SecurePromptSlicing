#include <stdio.h>
#include <string.h>

int main() {
    char vehicles[5][20] = {"Car", "Truck", "Motorcycle", "Bicycle", "Bus"};
    int index;

    printf("Enter the index of the vehicle (0-4): ");
    scanf("%d", &index);

    if (index >= 0 && index < 5) {
        printf("Vehicle at index %d is: %s\n", index, vehicles[index]);
    } else {
        printf("Invalid index. Please enter a number between 0 and 4.\n");
    }

    printf("\nList of all vehicles:\n");
    for (int i = 0; i < 5; i++) {
        printf("%d: %s\n", i, vehicles[i]);
    }

    return 0;
}