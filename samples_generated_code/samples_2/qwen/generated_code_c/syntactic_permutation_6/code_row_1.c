#include <stdio.h>
#include <string.h>

#define MAX_VEHICLES 5
#define VEHICLE_NAME_LENGTH 20

typedef struct {
    char name[VEHICLE_NAME_LENGTH];
} Vehicle;

int main() {
    Vehicle vehicles[MAX_VEHICLES] = {
        {"Car"},
        {"Bike"},
        {"Truck"},
        {"Bus"},
        {"Motorcycle"}
    };

    int index;
    printf("Enter the index of the vehicle (0 to %d): ", MAX_VEHICLES - 1);
    scanf("%d", &index);

    if (index >= 0 && index < MAX_VEHICLES) {
        printf("Selected Vehicle: %s\n", vehicles[index].name);
    } else {
        printf("Invalid index.\n");
    }

    printf("\nList of all vehicles:\n");
    for (int i = 0; i < MAX_VEHICLES; i++) {
        printf("%d. %s\n", i, vehicles[i].name);
    }

    return 0;
}