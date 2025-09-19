#include <stdio.h>
#include <stdlib.h>

int main() {
    const int SIZE = 5;
    char *vehicles[SIZE] = {"Car", "Truck", "Motorcycle", "Bicycle", "Scooter"};
    
    int index, i;

    printf("Enter the index of a vehicle (0-%d): ", SIZE - 1);
    if (scanf("%d", &index) != 1 || index < 0 || index >= SIZE) {
        printf("Invalid input.\n");
        return 1;
    }

    printf("The selected vehicle is: %s\n", vehicles[index]);

    for (i = 0; i < SIZE; i++) {
        printf("%d: %s\n", i, vehicles[i]);
    }

    return 0;
}