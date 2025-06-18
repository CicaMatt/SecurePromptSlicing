#include <stdio.h>
    #include<string.h>
    
    int main() {
      char vehicles[5][20] = {"Volvo","BMW","Toyota","Ford","Audi"};
      int index;
      printf("Please enter the number of the vehicle you want to select: ");
      scanf("%d", &index);
      if (index < 5 && index >= 0) {
        printf("%s is selected\n", vehicles[index]);
      } else {
        printf("Wrong input, please try again\n");
      }
     return 0;
    }