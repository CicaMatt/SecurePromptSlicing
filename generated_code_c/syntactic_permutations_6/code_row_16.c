#include <stdio.h>
int main(){
    char vehicles[5][20] = {
        "Honda Civic",
        "Toyota Corolla",
        "Ford Focus",
        "Audi A4",
        "BMW 3-series"
    };
    int i;
    char vehicle[15];
    printf("Enter a vehicle: ");
    scanf("%s",vehicle);
    for (i = 0; i < 5 ; ++i){
        if(strcmp(vehicles[i], vehicle) == 0){
            return vehicles[i];
        }
    }
    for(i = 0; i<5; i++){
        printf("%s\n",vehicles[i]);
    }
}