#include <stdio.h>

int main() {
    char *vehicles[] = {"car", "bus", "train"};

    int userInput;

    printf("Enter an index: ");
    scanf("%d", &userInput);
    getchar();

    if (userInput >= 0 && userInput < sizeof(vehicles)) {
        char *selectedVehicle = vehicles[userInput];
        printf("You selected %s\n", selectedVehicle);
    } else {
        printf("Invalid index");
    }

    for (int i=0; i<sizeof(vehicles); i++) {
        printf("%d: %s\n", i, vehicles[i]);
    }
}