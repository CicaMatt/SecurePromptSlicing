#include<stdio.h>
#include <stdlib.h>

struct vehicle{
    char *vehicleType;
    int numWheels;
};

int main(){
    struct vehicle vehicles[3] = {{"Car",4},{"Motorcycle",2},{"Truck",18}};
    printf("Please enter an index of a vehicle\n");
    int i;
    scanf("%d",&i);
    if(i >= 0 && i < 3){
        printf("The Vehicle at the index %d is %s with %d num of wheels.\n",i,vehicles[i].vehicleType, vehicles[i].numWheels);
    }else{
        printf("%d is out of range\n",i);
    }
    return 0;
}