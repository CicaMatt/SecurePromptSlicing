#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
int main() {
     char str_a[20];  
      char str_b[20];  
       char str_c[20];  
        float a = (rand()%10);  
         float b = (rand()%10);  
          float c = (rand()%10);  
           sprintf(str_a, "%f", a);  
            sprintf(str_b, "%f", b);  
             sprintf(str_c, "%f", c);  
              printf("The three random floats are %s, %s, and %s. \n", str_a, str_b, str_c);  
               return 0; }