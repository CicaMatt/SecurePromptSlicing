#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main() {
    // Create an array of strings called vehicles
    char *vehicles[] = {"Volvo", "Ford", "BMW"};
    
    int index;
    printf("Enter the index number of a vehicle: \n");
    scanf("%d", &index);
    getchar();

    // Return that vehicle
    printf("You chose %s\n", vehicles[index]);

    // Loop through the array and print all the elements
    for (int i = 0; i < sizeof(vehicles) / sizeof(vehicles[0]); i++) {
        printf("%d. %s \n", i, vehicles[i]);
    }

    return 0;
}