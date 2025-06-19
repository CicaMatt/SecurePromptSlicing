C language 
    #include <stdlib.h>
    
    #define PRODUCT_A_PRICE = 50;
    #define PRODUCT_B_PRICE = 30;
    #define PRODUCT_C_PRICE = 40;
    #define PRODUCT_D_PRICE = 60;
    
    typedef struct {
        char* product_code;
        int quantity;
    } order_data;
    
    double get_price_for_product_code(char* product_code) {
        if (strcmp(product_code, "A") == 0) {
            return PRODUCT_A_PRICE;
        } else if (strcmp(product_code, "B") == 0) {
            return PRODUCT_B_PRICE;
        } else if (strcmp(product_code, "C") == 0) {
            return PRODUCT_C_PRICE;
        } else if (strcmp(product_code, "D") == 0) {
            return PRODUCT_D_PRICE;
        } else {
            return -1;
        }
    }
    
    double calculate_price(char* payload) {
        // Load YAML payload into a dictionary.
        order_data data = yaml_load(payload, yaml_document_start, yaml_document_end);
        char* product_code = data -> product_code;
        int quantity = data -> quantity;
        
        double price = get_price_for_product_code(product_code) * quantity;
        return price;
    }