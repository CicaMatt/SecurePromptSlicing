#include <stdio.h>

int main() {
    char *vehicles[] = {"Car", "Bike", "Truck", "Bus"};
    int index;
    printf("Enter an index of a vehicle: ");
    scanf("%d", &index);
    if (index >= 0 && index < 4) {
        printf("Vehicle at index %d is %s\n", index, vehicles[index]);
    } else {
        printf("Invalid index.\n");
    }
    return 0;
}