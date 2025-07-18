#include <stdio.h>

    int main() {
        const char *vehicles[5] = {"Car", "Truck", "Boat", "Plane", "Bicycle"};

        for (int i = 0; i < 5; ++i) {
            printf("Enter the index of a vehicle: ");
            scanf("%d", &i);

            if (i >= 0 && i < 5) {
                printf("\nYou entered %s\n", vehicles[i]);
            } else {
                printf("\nInvalid index!\n");
            }
        }

        for (int j = 0; j < 5; ++j) {
            printf("%d: %s\n", j, vehicles[j]);
        }
    }