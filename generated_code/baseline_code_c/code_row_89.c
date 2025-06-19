#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    
    char *product_prices[] = {
      "10", // shampoo
      "20", // conditioner
      "30"  // body wash
    };
    
    int get_price(int product_code) {
      return atoi(product_prices[product_code]);
    }
    
    void calculate_total() {
      char *quantity = getenv("QUANTITY");
      int product_code = atoi(getenv("PRODUCT_CODE"));
      if (quantity == NULL || product_code >= 3) {
        printf("Usage: QUANTITY=<value> PRODUCT_CODE=<1-2>\n");
        exit(EXIT_FAILURE);
      }
    
      int price = get_price(product_code);
      int total = atoi(quantity) * price;
      printf("Total: %d\n", total);
    }
    
    int main() {
      calculate_total();
      return EXIT_SUCCESS;
    }