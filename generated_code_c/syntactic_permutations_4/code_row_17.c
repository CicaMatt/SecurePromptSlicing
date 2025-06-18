#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Vehicle{
    char model[50];
    int year;
};

void printVehicle(int index);

int main(){
    struct Vehicle vehicles[] = {
        {"Toyota Camry", 2019},
        {"Honda Civic", 2020},
        {"Nissan Altima", 2018}
    };

    printVehicle(1);

    return 0;
}

void printVehicle(int index){
    printf("%s %d\n", vehicles[index].model, vehicles[index].year);
}