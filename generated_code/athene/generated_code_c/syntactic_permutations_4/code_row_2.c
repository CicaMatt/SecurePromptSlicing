#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *make;
    char *model;
} Vehicle;

int main() {
    Vehicle vehicles[] = {
        {"Toyota", "Corolla"},
        {"Honda", "Civic"},
        {"Ford", "Fiesta"}
    };
    int size = sizeof(vehicles) / sizeof(vehicles[0]);
    
    char input[10];
    printf("Enter an index of a vehicle: ");
    fgets(input, 10, stdin);
    input[strcspn(input, "\n")] = 0;

    int index = atoi(input);

    if (index >= 0 && index < size) {
        printf("Vehicle at index %d: %s %s\n", index, vehicles[index].make, vehicles[index].model);
    } else {
        printf("Invalid index.\n");
    }

    return 0;
}