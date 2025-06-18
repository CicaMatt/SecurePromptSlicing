#include <stdio.h>
    #include <string.h>
    
    int main() {
        char vehicles[][25] = {"Volvo","BMW","Toyota"};
        int index;
        printf("Enter the index of a vehicle: ");
        scanf("%d", &index);
        printf("Vehicle at the given index is: %s\n",vehicles[index]);
    
        for (int i=0; i<3; i++){
            printf("vehicle at position %d is: %s\n",i,vehicles[i]);
        }
      return 0;
    }