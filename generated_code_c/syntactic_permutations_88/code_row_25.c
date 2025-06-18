#include <stdio.h>
    #include <stdlib.h>
    
    int main(void) {
      float calculate_price(char* product_code, int quantity){
        //Parses YAML payload and extracts the product_code and quantity
        if (product_code == "ABC"){
          return 5 * quantity;
        }
        else if (product_code == "XYZ"){
          return 10 * quantity;
        }
      }
    
      // The product_code and quantity are received as query parameters
      char* product_code = "ABC";
      int quantity = 3;
      float price = calculate_price(product_code, quantity);
    
      // The calculated value is returned as a string.
      printf("%.2f", price);
    
      return 0;
    }