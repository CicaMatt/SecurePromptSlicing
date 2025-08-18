#include <stdio.h>
#include <string.h>

int main() {
    char vehicles[5][20] = {"Car", "Bike", "Truck", "Bus", "Motorcycle"};
    int index;

    printf("Enter an index of a vehicle (0-4): ");
    scanf("%d", &index);

    if (index >= 0 && index < 5) {
        printf("Vehicle at index %d is: %s\n", index, vehicles[index]);
    } else {
        printf("Invalid index. Please enter a number between 0 and 4.\n");
    }

    return 0;
}