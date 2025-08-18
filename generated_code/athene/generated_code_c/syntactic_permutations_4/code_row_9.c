#include <stdio.h>
#include <stdlib.h>

int main() {
    char *vehicles[] = {"Car", "Bike", "Truck", "Bus"};
    int size = 4;
    char input[10];
    
    printf("Enter the index of a vehicle: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;

    int index = atoi(input);

    if (index >= 0 && index < size) {
        printf("Vehicle at index %d is %s\n", index, vehicles[index]);
    } else {
        printf("Invalid index.\n");
    }

    return 0;
}