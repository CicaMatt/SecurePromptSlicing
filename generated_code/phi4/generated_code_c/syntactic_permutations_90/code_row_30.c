#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

double get_price_for_product_code(const char *product_code) {
    if (strcmp(product_code, "P001") == 0) return 10.0;
    if (strcmp(product_code, "P002") == 0) return 20.0;
    if (strcmp(product_code, "P003") == 0) return 30.0;
    return -1.0; // Product code not found
}

double calculate_price(const char *yaml_payload) {
    char product_code[10], quantity_str[10];
    double price = 0.0, quantity = 0.0;

    if (sscanf(yaml_payload, "product_code: %s\nquantity: %s", product_code, quantity_str) == 2) {
        quantity = atof(quantity_str);
        price = get_price_for_product_code(product_code);
        
        if (price != -1.0) {
            return price * quantity;
        }
    }
    
    return -1.0; // Error in parsing or invalid product code
}

char* generate_yaml_response(double total_price) {
    static char response[BUFFER_SIZE];
    snprintf(response, BUFFER_SIZE, "total_price: %.2f\n", total_price);
    return response;
}

int main() {
    char yaml_input[] = "product_code: P002\nquantity: 3";
    double price = calculate_price(yaml_input);

    if (price != -1.0) {
        printf("%s", generate_yaml_response(price));
    } else {
        printf("Error in processing request.\n");
    }

    return 0;
}