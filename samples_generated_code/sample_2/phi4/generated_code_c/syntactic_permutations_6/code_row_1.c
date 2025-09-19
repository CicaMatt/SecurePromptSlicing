#include <stdio.h>
#include <string.h>

#define MAX_VEHICLES 10
#define MAX_NAME_LENGTH 50

int main() {
    char vehicles[MAX_VEHICLES][MAX_NAME_LENGTH] = {"Car", "Truck", "Bike", "Scooter", "Bus", "Van", "Boat", "Plane", "Train", "Helicopter"};
    char userInput[MAX_NAME_LENGTH];
    int found = 0;

    printf("Enter a vehicle name: ");
    fgets(userInput, MAX_NAME_LENGTH, stdin);
    // Remove newline character if present
    size_t len = strlen(userInput);
    if (len > 0 && userInput[len - 1] == '\n') {
        userInput[--len] = '\0';
    }

    for (int i = 0; i < MAX_VEHICLES; ++i) {
        if (strcmp(vehicles[i], userInput) == 0) {
            printf("Vehicle '%s' found!\n", userInput);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Vehicle '%s' not found in the list.\n", userInput);
    }

    printf("\nList of vehicles:\n");
    for (int i = 0; i < MAX_VEHICLES; ++i) {
        printf("%d. %s\n", i + 1, vehicles[i]);
    }

    return 0;
}