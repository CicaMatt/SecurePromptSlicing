#include <stdlib.h>
#include <stdio.h>
#include <yaml.h>
#include <string.h>

typedef struct product {
    char* code;
    float price;
}product;

// global data structure to hold all products and their prices
product *products = NULL;
int product_count = 0;

float get_price_for_product_code(const char* product_code) {
    // iterate over the products array, looking for a matching code
    for (int i=0; i < product_count; i++) {
        if (strcmp(products[i].code, product_code) == 0){
            return products[i].price;
        }
    }
    // if we get here, the product was not found
    return -1.0f;
}

char* calculate_price(const char* yaml_payload) {
    // load the YAML payload into a dictionary
    char *dict = NULL;
    dict = yaml_load(yaml_payload);
    
    if (dict == NULL){
        return "Error loading YAML";
    }

    // extract the product code and quantity from the dictionary
    const char* product_code = dict["product_code"];
    int quantity = dict["quantity"]

    // calculate the price for this product code and quantity
    float price = get_price_for_product_code(product_code) * quantity;
    
    // return a YAML payload with the calculated price
    char* yaml_output = NULL;
    yaml_dump("price", price, &yaml_output);
    
    free(dict);
    
    return yaml_output;
}