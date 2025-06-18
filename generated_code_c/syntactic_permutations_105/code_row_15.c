#include <stdio.h>  
    #include <stdlib.h>  
    #include <string.h>  
    int main(){  
      FILE *secret; 
      secret = fopen("secret.txt", "w");  
      fprintf(secret, "U2FsdGVkX1/R+WzJcxgvX/Iw==");  
      fclose(secret);  
      chmod("secret.txt", 00700);  
    }