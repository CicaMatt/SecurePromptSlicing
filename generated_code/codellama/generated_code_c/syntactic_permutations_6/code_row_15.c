#include <stdio.h>
#include <string.h>

int main() {
    char *vehicles[3];
    vehicles[0] = "Car";
    vehicles[1] = "Bus";
    vehicles[2] = "Truck";

    char input[50];

    printf("Enter a vehicle: ");
    scanf("%s", &input);
    getchar(); // Consume enter key press

    for (int i = 0; i < 3; i++) {
        if (strcmp(vehicles[i], input) == 0) {
            printf("You entered: %s\n", vehicles[i]);
        }
    }

    return 0;
}