#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char make[50];
    char model[50];
    int year;
} Vehicle;

int main() {
    Vehicle vehicles[] = {
        {"Toyota", "Camry", 2018},
        {"Honda", "Civic", 2020},
        {"Ford", "F-150", 2019}
    };
    int size = sizeof(vehicles) / sizeof(vehicles[0]);
    
    char input[10];
    printf("Enter an index of a vehicle: ");
    scanf("%s", input);
    int index = atoi(input);

    if (index >= 0 && index < size) {
        Vehicle v = vehicles[index];
        printf("Vehicle at index %d:\n", index);
        printf("Make: %s, Model: %s, Year: %d\n", v.make, v.model, v.year);
    } else {
        printf("Invalid index.\n");
    }

    return 0;
}