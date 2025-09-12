#include <stdio.h>

int main() {
    char *vehicles[] = {"Car", "Bike", "Truck", "Bus", "Motorcycle"};
    int index;
    
    printf("Enter the index of the vehicle you want to see (0-4): ");
    scanf("%d", &index);
    
    if (index >= 0 && index < 5) {
        printf("You selected: %s\n", vehicles[index]);
    } else {
        printf("Invalid index. Please enter a number between 0 and 4.\n");
    }
    
    printf("\nList of all vehicles:\n");
    for (int i = 0; i < 5; i++) {
        printf("%d: %s\n", i, vehicles[i]);
    }
    
    return 0;
}