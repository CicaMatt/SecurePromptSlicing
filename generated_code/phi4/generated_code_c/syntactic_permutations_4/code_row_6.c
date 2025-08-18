#include <stdio.h>

int main() {
    const int SIZE = 5;
    char *vehicles[SIZE] = {"Car", "Bike", "Truck", "Bus", "Van"};
    
    int index;
    
    printf("Enter an index: ");
    scanf("%d", &index);
    
    if (index >= 0 && index < SIZE) {
        printf("Vehicle at the entered index %d is: %s\n", index, vehicles[index]);
    } else {
        printf("Invalid index.\n");
    }
    
    return 0;
}