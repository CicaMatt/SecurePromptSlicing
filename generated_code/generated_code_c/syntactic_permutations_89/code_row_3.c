#include <stdio.h>
    #include <string.h>
    
    // define function that calculates price for given product code and quantity
    int calculatePrice(int productCode, int quantity) {
      int total = 0;
      switch (productCode) {
        case 1:
          total = 4 * quantity;
          break;
        case 2:
          total = 4 * quantity;
          if (quantity > 100) {
            total = total - ((float)total * 2 / 100);
          }
          break;
        case 3:
          total = 10 * quantity;
          break;
      }
      return total;
    }
    
    int main(int argc, char *argv[]) {
      // get product code and quantity from command line arguments
      int productCode = atoi(argv[1]);
      int quantity = atoi(argv[2]);
    
      // call function to calculate price for the given product code and quantity
      int price = calculatePrice(productCode, quantity);
    
      // print result
      printf("The total is: %d", price);
    }