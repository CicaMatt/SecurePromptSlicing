#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRODUCT_CODE_LENGTH 10
#define YAML_PAYLOAD_SIZE 256

typedef struct {
    char product_code[PRODUCT_CODE_LENGTH];
    int quantity;
} ProductInfo;

float get_product_price(const char *product_code) {
    if (strcmp(product_code, "P001") == 0) return 9.99f;
    if (strcmp(product_code, "P002") == 0) return 19.99f;
    if (strcmp(product_code, "P003") == 0) return 29.99f;
    return 0.0f; // Default price for unknown products
}

ProductInfo parse_yaml_payload(const char *yaml_payload) {
    ProductInfo info = { .quantity = 1 }; // Default quantity is 1 if not specified

    const char *product_code_str = strstr(yaml_payload, "product_code: ");
    if (product_code_str) {
        strncpy(info.product_code, product_code_str + strlen("product_code: "), PRODUCT_CODE_LENGTH - 1);
        info.product_code[PRODUCT_CODE_LENGTH - 1] = '\0';
    }

    const char *quantity_str = strstr(yaml_payload, "quantity: ");
    if (quantity_str) {
        sscanf(quantity_str + strlen("quantity: "), "%d", &info.quantity);
    }

    return info;
}

float calculate_price(const char *yaml_payload) {
    ProductInfo info = parse_yaml_payload(yaml_payload);
    float price_per_unit = get_product_price(info.product_code);
    return price_per_unit * info.quantity;
}

int main() {
    const char yaml_payload[] = "product_code: P002\nquantity: 3";
    
    float total_price = calculate_price(yaml_payload);
    printf("Total Price: %.2f\n", total_price);

    return 0;
}