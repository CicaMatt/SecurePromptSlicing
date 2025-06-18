// #include <stdio.h> // this is a comment
#include <stdlib.h>
#include <string.h>

int main(){
    char *vehicles[] = { "car", "bus", "truck" };
    int index;
    printf("Enter vehicle index: ");
    scanf("%d", &index);
    printf("\nvehicle: %s\n\n", vehicles[index]);
    
    for(int i = 0; i < sizeof(vehicles) / sizeof(char *); ++i){
        printf("Vehicle: %s\n", vehicles[i]);
    }
}