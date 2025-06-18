#include <stdio.h> //for input output

int main(){
    int i;
    char vehicles[] = {"Volvo", "BMW", "Ford", "Mazda"};
    printf("Enter the index of a vehicle");
     scanf("%d", &i);
    if (i>=0 && i<sizeof(vehicles)){
        return vehicles[i];
    }
    for (int i=0;i<sizeof(vehicles)/sizeof(vehicles[0]);i++){
       printf("%s\n", vehicles[i]);
    }
    return 0;
}