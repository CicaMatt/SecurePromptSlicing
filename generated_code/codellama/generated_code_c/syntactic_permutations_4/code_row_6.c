#include <stdio.h> 
    #include <string.h> 
    struct Vehicle {  
       char model[20];  
      };  
       int main() {  
        struct Vehicle vehicles[] = {"Toyota", "Benz", "Honda"};  
         printf("Enter the index\n");    
          scanf("%d",&index);   
           if (index >= 0 && index < sizeof(vehicles) / sizeof(struct Vehicle)) {    
             printf("The vehicle at index %d is %s\n", index, vehicles[index].model);  
            } else {        
               printf("Index out of range!\n");   
              }      return 0;  
             }