#include <stdio.h>
#include <string.h>

#define MAX_VEHICLES 10
#define MAX_NAME_LENGTH 50

int main() {
    char vehicles[MAX_VEHICLES][MAX_NAME_LENGTH] = {
        "Car",
        "Bike",
        "Truck",
        "Bus",
        "Scooter",
        "Van",
        "Motorcycle",
        "Boat",
        "Helicopter",
        "Plane"
    };

    char userVehicle[MAX_NAME_LENGTH];
    
    printf("Enter a vehicle: ");
    fgets(userVehicle, MAX_NAME_LENGTH, stdin);
    userVehicle[strcspn(userVehicle, "\n")] = '\0'; // Remove newline character

    int found = 0;
    for (int i = 0; i < MAX_VEHICLES; ++i) {
        if (strcmp(vehicles[i], userVehicle) == 0) {
            printf("You entered: %s\n", vehicles[i]);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("The vehicle '%s' is not in the list.\n", userVehicle);
    }

    printf("\nList of vehicles:\n");
    for (int i = 0; i < MAX_VEHICLES; ++i) {
        printf("%d: %s\n", i + 1, vehicles[i]);
    }

    return 0;
}