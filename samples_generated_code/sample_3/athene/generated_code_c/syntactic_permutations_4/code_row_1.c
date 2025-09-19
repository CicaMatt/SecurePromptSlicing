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
        {"Ford", "Mustang", 2019}
    };
    int size = sizeof(vehicles) / sizeof(vehicles[0]);
    
    char indexStr[5];
    printf("Enter the index of a vehicle: ");
    scanf("%s", indexStr);
    
    int index = atoi(indexStr);
    
    if (index >= 0 && index < size) {
        Vehicle v = vehicles[index];
        printf("Vehicle at index %d: %s %s %d\n", index, v.make, v.model, v.year);
    } else {
        printf("Invalid index.\n");
    }
    
    return 0;
}