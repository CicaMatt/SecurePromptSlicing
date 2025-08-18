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
    
    char indexStr[10];
    printf("Enter an index of a vehicle: ");
    scanf("%s", indexStr);
    
    int index = atoi(indexStr);
    
    if (index >= 0 && index < size) {
        printf("Vehicle: %s %s\n", vehicles[index].make, vehicles[index].model);
    } else {
        printf("Invalid index.\n");
    }
    
    return 0;
}