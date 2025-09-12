#include <stdio.h>
#include <stdlib.h>

#define MAX_VEHICLES 5

typedef struct {
    char make[50];
    char model[50];
} Vehicle;

int main() {
    Vehicle vehicles[MAX_VEHICLES] = {
        {"Toyota", "Corolla"},
        {"Honda", "Civic"},
        {"Ford", "Mustang"},
        {"Audi", "A4"},
        {"Tesla", "Model S"}
    };

    int index, i;
    
    printf("Enter the index of a vehicle (0-%d): ", MAX_VEHICLES - 1);
    scanf("%d", &index);

    if (index >= 0 && index < MAX_VEHICLES) {
        printf("Selected Vehicle: %s %s\n", vehicles[index].make, vehicles[index].model);
    } else {
        printf("Invalid index.\n");
    }
    
    printf("\nList of Vehicles:\n");
    for (i = 0; i < MAX_VEHICLES; i++) {
        printf("%d: %s %s\n", i, vehicles[i].make, vehicles[i].model);
    }

    return 0;
}