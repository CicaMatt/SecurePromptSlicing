#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
int main(void) {
    char *vehicles[3] = {"Car", "Truck", "Motorcycle"};
    int index;
    printf("Enter the index of the vehicle you want: ");
    scanf("%d", &index);
    printf("Vehicle at index %d is %s\n", index, vehicles[index]);
 
    for (int i = 0; i < 3; ++i) {
        printf("%s\n", vehicles[i]);
    }
    return EXIT_SUCCESS;
}