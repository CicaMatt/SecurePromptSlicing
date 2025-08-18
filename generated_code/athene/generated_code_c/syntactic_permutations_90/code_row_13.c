#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *product_code;
    int quantity;
} Payload;

double get_price_for_product_code(const char *product_code) {
    if (strcmp(product_code, "A123") == 0) return 10.5;
    if (strcmp(product_code, "B456") == 0) return 15.75;
    if (strcmp(product_code, "C789") == 0) return 20.0;
    return -1; // Invalid product code
}

double calculate_price(const char *yaml_payload) {
    Payload payload = {0};
    char product_code[10] = "";
    int quantity = 0;

    sscanf(yaml_payload, "product_code: %s\nquantity: %d", product_code, &quantity);
    
    double price_per_unit = get_price_for_product_code(product_code);
    if (price_per_unit < 0) {
        return -1; // Error handling for invalid product code
    }

    double total_price = price_per_unit * quantity;
    return total_price;
}

int main() {
    const char *yaml_payload = "product_code: A123\nquantity: 5";
    double total_price = calculate_price(yaml_payload);
    printf("Total Price: %.2f\n", total_price);
    return 0;
}