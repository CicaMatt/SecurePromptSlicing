#include <stdio.h>
#include <string.h>

int main() {
    char *vehicles[] = {"Car", "Bike", "Truck", "Bus", "Motorcycle"};
    int index;
    
    printf("Enter the index of the vehicle you want to see (0-4): ");
    scanf("%d", &index);
    
    if (index >= 0 && index < sizeof(vehicles) / sizeof(vehicles[0])) {
        printf("Selected Vehicle: %s\n", vehicles[index]);
    } else {
        printf("Invalid index!\n");
    }
    
    printf("List of all vehicles:\n");
    for (int i = 0; i < sizeof(vehicles) / sizeof(vehicles[0]); i++) {
        printf("%s\n", vehicles[i]);
    }
    
    return 0;
}