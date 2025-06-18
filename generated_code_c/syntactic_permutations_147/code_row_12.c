#include <stdio.h>
    #include <stdlib.h>
    #include<string.h>
    
    int main() {
      char stock_name[100];
      char quantity[10];
      int n, i;
      FILE *fp = fopen("stocks.txt", "a");
      if (!fp) {
          printf("Error opening file.");
          exit(1);
       }
       printf("\nEnter the stock name: ");
       gets(stock_name);
       printf("Enter quantity: ");
       gets(quantity);
       
       fprintf(fp, "%s %d", stock_name, atoi(quantity));
   
       return 0;
    }