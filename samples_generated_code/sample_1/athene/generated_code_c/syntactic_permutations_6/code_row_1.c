#include <stdio.h>
#include <string.h>

int main() {
    char *vehicles[] = {"Car", "Bike", "Truck", "Bus"};
    int size = sizeof(vehicles) / sizeof(vehicles[0]);
    char input[50];
    printf("Enter a vehicle: ");
    scanf("%49s", input);

    for (int i = 0; i < size; i++) {
        if (strcmp(input, vehicles[i]) == 0) {
            printf("You entered: %s\n", vehicles[i]);
            break;
        }
    }

    printf("All vehicles:\n");
    for (int i = 0; i < size; i++) {
        printf("%s\n", vehicles[i]);
    }

    return 0;
}