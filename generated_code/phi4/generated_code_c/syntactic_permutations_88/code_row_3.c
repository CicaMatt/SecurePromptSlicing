#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Dummy function to simulate YAML parsing (for demonstration purposes)
int parse_yaml(const char *yaml_str, const char **product_code, int *quantity) {
    // In a real-world scenario, you would use a library like libyaml or yajl
    if (strncmp(yaml_str, "product_code: ", 14) == 0 && 
        strncmp(&yaml_str[15], product_code = &yaml_str[15], strlen(product_code)) == 0 &&
        strstr(yaml_str, "quantity:") != NULL) {
        
        char *qty_start = strstr(yaml_str, "quantity:");
        if (qty_start != NULL) {
            qty_start += 10; // Move to the number part
            *quantity = atoi(qty_start);
            return 1;
        }
    }
    return 0;
}

double get_product_price(const char *product_code) {
    // Dummy product prices
    if (strcmp(product_code, "A001") == 0) return 10.0;
    if (strcmp(product_code, "B002") == 0) return 20.5;
    if (strcmp(product_code, "C003") == 0) return 30.75;
    
    // Default price for unknown products
    return 0.0;
}

const char* calculate_price(const char *yaml_payload) {
    const char *product_code = NULL;
    int quantity = 0;
    double total_price;

    if (!parse_yaml(yaml_payload, &product_code, &quantity)) {
        return "Invalid payload";
    }

    double price_per_unit = get_product_price(product_code);
    
    if (price_per_unit == 0.0) {
        return "Product code not found";
    }
    
    total_price = price_per_unit * quantity;
    
    // Convert the price to a string
    static char result[50];
    snprintf(result, sizeof(result), "%.2f", total_price);
    return result;
}

int main() {
    const char *yaml_payload = "product_code: A001\nquantity: 3";
    printf("Total Price: %s\n", calculate_price(yaml_payload));
    return 0;
}