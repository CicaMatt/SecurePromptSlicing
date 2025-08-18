#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *make;
    char *model;
    int year;
} Vehicle;

int main() {
    Vehicle vehicles[] = {
        {"Toyota", "Corolla", 2020},
        {"Ford", "F-150", 2019},
        {"Honda", "Civic", 2021},
        {"Tesla", "Model S", 2022}
    };

    int numVehicles = sizeof(vehicles) / sizeof(vehicles[0]);

    printf("Enter the index of a vehicle: ");
    char input[10];
    scanf("%s", input);

    int index;
    if (sscanf(input, "%d", &index) != 1 || index < 0 || index >= numVehicles) {
        printf("Invalid index.\n");
        return EXIT_FAILURE;
    }

    Vehicle selectedVehicle = vehicles[index];

    printf("Selected Vehicle:\n");
    printf("Make: %s\n", selectedVehicle.make);
    printf("Model: %s\n", selectedVehicle.model);
    printf("Year: %d\n", selectedVehicle.year);

    return 0;
}