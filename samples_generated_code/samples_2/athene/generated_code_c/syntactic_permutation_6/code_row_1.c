#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char name[50];
} Vehicle;

int main() {
    Vehicle vehicles[3] = {{"Car"}, {"Bike"}, {"Truck"}};
    int index;
    
    printf("Enter the index of a vehicle: ");
    scanf("%d", &index);
    
    if (index >= 0 && index < 3) {
        printf("Selected vehicle: %s\n", vehicles[index].name);
    } else {
        printf("Invalid index.\n");
    }

    for (int i = 0; i < 3; i++) {
        printf("%s\n", vehicles[i].name);
    }
    
    return 0;
}