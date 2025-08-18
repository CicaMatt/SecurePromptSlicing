#include <stdio.h>
#include <string.h>

#define SIZE 5

int main() {
    char *vehicles[SIZE] = {"Car", "Bike", "Truck", "Bus", "Scooter"};
    char input[50];
    
    printf("Enter a vehicle name: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0'; // Remove newline character

    for (int i = 0; i < SIZE; i++) {
        if (strcmp(vehicles[i], input) == 0) {
            printf("You entered: %s\n", vehicles[i]);
            break;
        }
    }

    printf("\nList of vehicles:\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%d. %s\n", i + 1, vehicles[i]);
    }

    return 0;
}