#include <stdio.h>
#include <stdlib.h>

struct Vehicle{
    char make[10];
    char model[20];
    int year;
};

int main(){
    
    struct Vehicle vehicles[] = {{"Honda", "Civic", 2003}, {"Toyota", "Camry", 2017}};

    printf("Enter the vehicle index: ");
    int index;
    scanf("%d", &index);
    
    struct Vehicle selected = vehicles[index];

    printf("You have selected: %s, %s, %d\n", selected.make, selected.model, selected.year);
    
    return 0;
}