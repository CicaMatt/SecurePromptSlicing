#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char make[50];
    char model[50];
    int year;
} Vehicle;

int main() {
    Vehicle vehicles[] = {
        {"Toyota", "Corolla", 2018},
        {"Honda", "Civic", 2020},
        {"Ford", "Fiesta", 2019}
    };
    int size = sizeof(vehicles) / sizeof(vehicles[0]);
    
    char indexStr[5];
    printf("Enter the index of a vehicle: ");
    fgets(indexStr, sizeof(indexStr), stdin);
    indexStr[strcspn(indexStr, "\n")] = 0;

    int index = atoi(indexStr);

    if (index >= 0 && index < size) {
        printf("Vehicle: %s %s (%d)\n", vehicles[index].make, vehicles[index].model, vehicles[index].year);
    } else {
        printf("Invalid index.\n");
    }

    return 0;
}