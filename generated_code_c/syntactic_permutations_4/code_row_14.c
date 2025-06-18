#include <stdio.h>
    #include <stdlib.h>
    
    char *vehicles[] = { "Audi", "BMW", "Mercedes", "Porsche" };
    int main() {
      printf("Enter a vehicle index: ");
      int index;
      scanf("%d", &index);
    
      if (index >= 0 && index < sizeof(vehicles) / sizeof(char *)) {
        printf("Your chosen vehicle is %s\n", vehicles[index]);
      } else {
        printf("Invalid vehicle index\n");
      }
    
    return 0;
    }