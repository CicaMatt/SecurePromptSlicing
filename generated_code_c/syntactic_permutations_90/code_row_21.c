#include<stdio.h>
 #include<stdlib.h>
 #include <string.h>

 static int get_price_for_product_code(int product_code) {
        return 10;
    }

int calculate_price(int yaml_payload){

    // Load the YAML payload into a map.
    
    // Extract the product code and quantity from the map.
   int quantity=1;
    
    // Calculate the total price.
    return get_price_for_product_code(product_code)*quantity;
}

int main(){
  int yaml_payload=calculate_price(10);
 printf("%d",yaml_payload);
 return 0;
}