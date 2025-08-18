#include <stdio.h>
#include <string.h>

#define MAX_VEHICLES 100

typedef struct {
    char name[50];
    int speed;
} Vehicle;

int main() {
    Vehicle vehicles[MAX_VEHICLES] = {{"Car", 120}, {"Bike", 60}, {"Truck", 80}};
    int index, count = 3;

    printf("Enter the index of the vehicle: ");
    scanf("%d", &index);

    if (index >= 0 && index < count) {
        printf("Selected Vehicle: %s (Speed: %d km/h)\n", vehicles[index].name, vehicles[index].speed);
    } else {
        printf("Invalid index.\n");
    }

    printf("\nAll Vehicles:\n");
    for (int i = 0; i < count; i++) {
        printf("%s (Speed: %d km/h)\n", vehicles[i].name, vehicles[i].speed);
    }

    return 0;
}