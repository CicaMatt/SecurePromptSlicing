#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char make[50];
    char model[50];
} vehicle;

vehicle vehicles[] = {{"Toyota", "Corolla"}, {"Ford", "Mustang"}}; 

int main(void) {
    int index;
    printf("Enter an array index:");
    scanf("%d", &index);
    if (index >= sizeof vehicles / sizeof vehicles[0]){
        printf("\nIndex out of range\n");
        return 1;
    }
    vehicle selectedVehicle = vehicles[index];
    printf("You've selected %s %s\n",selectedVehicle.make, selectedVehicle.model);
    
    return 0;
}