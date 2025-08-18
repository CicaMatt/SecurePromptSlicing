#include <stdio.h>

typedef struct {
    char make[50];
    char model[50];
    int year;
} Vehicle;

void printVehicle(const Vehicle *v) {
    printf("Make: %s\n", v->make);
    printf("Model: %s\n", v->model);
    printf("Year: %d\n", v->year);
}

int main() {
    Vehicle vehicles[] = {
        {"Toyota", "Corolla", 2020},
        {"Honda", "Civic", 2019},
        {"Ford", "Mustang", 2021},
        {"Tesla", "Model S", 2022}
    };

    int numVehicles = sizeof(vehicles) / sizeof(vehicles[0]);
    int index;

    printf("Enter the index of the vehicle (0 to %d): ", numVehicles - 1);
    scanf("%d", &index);

    if (index >= 0 && index < numVehicles) {
        printVehicle(&vehicles[index]);
    } else {
        printf("Invalid index.\n");
    }

    return 0;
}