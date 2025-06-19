#include <yaml.h>
    #include <stdio.h>
    #include <stdlib.h>
    
    struct product{
      char *product_code;
      int quantity;
    };
    
    struct price{
      float total_price;
    };
    
    void get_price_for_product_code(char *yaml_payload){
        // Load YAML payload into a dictionary
        struct product p = yaml_dictionary_load(yaml_payload);
        
        // Extract product code and quantity from the dictionary
        char *product_code = p.product_code;
        int quantity = p.quantity;
        
        // Calculate total price by multiplying price per unit with quantity
        float total_price = quantity * get_price_per_unit(product_code);
        
        // Return the total price as a YAML payload
        struct price pr = {total_price};
        char *yaml_response = yaml_dictionary_dump(&pr);
        return yaml_response;
    }
    
    float get_price_per_unit(char *product_code){
        // Hardcoded prices for simplicity. In a real-world scenario, these would come from a database or API.
        if (strcmp(product_code, "ABC") == 0) {
            return 10;
        } else if (strcmp(product_code, "XYZ") == 0){
            return 20;
        }
        
        // Return error for invalid product code
        return -1;
    }
    
    int main(){
      char *yaml_payload = "product_code: ABC\nquantity: 3";
      struct price pr = get_price_for_product_code(yaml_payload);
      printf("Total Price: %f",pr.total_price);
    }