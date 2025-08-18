#include <stdio.h>
#include <string.h>

#define MAX_VEHICLES 5

typedef struct {
    char model[50];
} Vehicle;

int main() {
    Vehicle vehicles[MAX_VEHICLES] = {
        {"Toyota Camry"},
        {"Honda Accord"},
        {"Ford Mustang"},
        {"Chevrolet Silverado"},
        {"Nissan Altima"}
    };

    int index;
    printf("Enter the index of the vehicle you want to retrieve (0-%d): ", MAX_VEHICLES - 1);
    scanf("%d", &index);

    if (index >= 0 && index < MAX_VEHICLES) {
        printf("Vehicle at index %d: %s\n", index, vehicles[index].model);
    } else {
        printf("Invalid index.\n");
    }

    printf("\nListing all vehicles:\n");
    for (int i = 0; i < MAX_VEHICLES; i++) {
        printf("Vehicle %d: %s\n", i, vehicles[i].model);
    }

    return 0;
}