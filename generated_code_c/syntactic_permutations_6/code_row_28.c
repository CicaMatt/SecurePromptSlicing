#include<stdio.h>
#include <string.h>
int main() {
    int size = 5;
    char *vehicles[size];
    
    vehicles[0] = "car";
    vehicles[1] = "bus";
    vehicles[2] = "truck";
    vehicles[3] = "train";
    vehicles[4] = "plane";
    
    int index;
    printf("Enter the index of a vehicle: ");
    scanf("%d", &index);
    
    if (index > size || index < 0) {
        printf("Index out of range\n");
    } else {
        printf("%s\n", vehicles[index]);
    }
    
    for (int i = 0; i < size; ++i) {
        printf("%s ", vehicles[i]);
    }
    return 0;
}