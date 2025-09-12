#include <stdio.h>
#include <string.h>

int main() {
    char *vehicles[] = {"Car", "Bike", "Truck", "Bus"};
    int index;
    printf("Enter the index of a vehicle: ");
    scanf("%d", &index);
    if (index >= 0 && index < 4) {
        printf("Vehicle at index %d is %s\n", index, vehicles[index]);
    } else {
        printf("Invalid index!\n");
    }
    return 0;
}