#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Vehicle {
    char make[10];
    int model;
};

int main() {
    struct Vehicle vehicles[] = {{"Toyota", 2019}, {"Honda", 2018}, {"Ford", 2020}};
    printf("Enter the index of a vehicle: ");
    int idx;
    scanf("%d", &idx);
    printf("You selected %s %d\n", vehicles[idx].make, vehicles[idx].model);
    return 0;
}