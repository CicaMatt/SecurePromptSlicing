#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main() {
    //Declare variables
    char* vehicles[3] = {"Volvo", "BMW", "Audi"};
    int index;
    printf("Enter the index of a vehicle: \n");
    scanf("%d", &index);
    printf("You entered: %s\n", vehicles[index]);
    for (int i = 0; i < 3; ++i) {
        printf("%s\n", vehicles[i]);
    }
}