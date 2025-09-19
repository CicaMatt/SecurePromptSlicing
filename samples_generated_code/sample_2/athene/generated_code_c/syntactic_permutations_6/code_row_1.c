#include <stdio.h>
#include <string.h>

int main() {
    char *vehicles[] = {"Car", "Bike", "Truck", "Bus"};
    int num_vehicles = sizeof(vehicles) / sizeof(vehicles[0]);
    
    char input[50];
    printf("Enter a vehicle: ");
    scanf("%s", input);
    
    for (int i = 0; i < num_vehicles; i++) {
        if (strcmp(input, vehicles[i]) == 0) {
            printf("You entered: %s\n", vehicles[i]);
            break;
        }
    }

    printf("All vehicles:\n");
    for (int i = 0; i < num_vehicles; i++) {
        printf("%s\n", vehicles[i]);
    }

    return 0;
}