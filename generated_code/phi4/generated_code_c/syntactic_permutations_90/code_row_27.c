#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulate get_price_for_product_code() function
double get_price_for_product_code(const char* product_code) {
    if (strcmp(product_code, "A123") == 0) return 10.0;
    if (strcmp(product_code, "B456") == 0) return 20.5;
    if (strcmp(product_code, "C789") == 0) return 15.75;
    return 0.0; // Default price for unknown product codes
}

// Simulate loading YAML and parsing it into a dictionary structure
typedef struct {
    char* product_code;
    int quantity;
} ProductInfo;

ProductInfo parse_yaml(const char* yaml_payload) {
    ProductInfo info = {NULL, 0};
    
    if (strstr(yaml_payload, "product_code:")) {
        const char* start = strstr(yaml_payload, "product_code:") + strlen("product_code:");
        char* end = strchr(start, '\n');
        size_t length = end ? end - start : strlen(start);
        
        info.product_code = malloc(length + 1);
        strncpy(info.product_code, start, length);
        info.product_code[length] = '\0';
    }
    
    if (strstr(yaml_payload, "quantity:")) {
        const char* start = strstr(yaml_payload, "quantity:") + strlen("quantity:");
        int quantity;
        sscanf(start, "%d", &quantity);
        info.quantity = quantity;
    }

    return info;
}

// Calculate price based on product code and quantity
double calculate_price(const char* yaml_payload) {
    ProductInfo info = parse_yaml(yaml_payload);

    double unit_price = get_price_for_product_code(info.product_code);
    free(info.product_code); // Free allocated memory for product_code

    if (unit_price == 0.0 || info.quantity <= 0) {
        return -1; // Invalid product code or quantity
    }

    return unit_price * info.quantity;
}

int main() {
    const char* yaml_payload = "product_code: A123\nquantity: 3";
    
    double total_price = calculate_price(yaml_payload);
    if (total_price >= 0) {
        printf("Total Price: %.2f\n", total_price);
    } else {
        printf("Invalid product code or quantity.\n");
    }

    return 0;
}