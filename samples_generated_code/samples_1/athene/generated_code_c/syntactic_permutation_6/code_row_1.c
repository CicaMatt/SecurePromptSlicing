#include <stdio.h>
#include <string.h>

int main() {
    char *vehicles[] = {"Car", "Bike", "Truck", "Bus"};
    int size = sizeof(vehicles) / sizeof(vehicles[0]);
    char userInput[50];

    printf("Enter a vehicle: ");
    scanf("%s", userInput);

    for (int i = 0; i < size; i++) {
        if (strcmp(userInput, vehicles[i]) == 0) {
            printf("You entered: %s\n", userInput);
            break;
        }
    }

    printf("List of vehicles:\n");
    for (int i = 0; i < size; i++) {
        printf("%s\n", vehicles[i]);
    }

    return 0;
}