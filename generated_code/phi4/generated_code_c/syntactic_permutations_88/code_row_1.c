#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRODUCT_LIST_SIZE 3

typedef struct {
    char *product_code;
    float price;
} Product;

Product products[PRODUCT_LIST_SIZE] = {
    {"P001", 10.99},
    {"P002", 15.49},
    {"P003", 8.75}
};

float get_product_price(const char *code) {
    for (int i = 0; i < PRODUCT_LIST_SIZE; ++i) {
        if (strcmp(products[i].product_code, code) == 0) {
            return products[i].price;
        }
    }
    return -1.0;
}

const char* parse_yaml_payload(const char *payload, const char **product_code, int *quantity) {
    // Simplified YAML parsing logic for the given example
    static char parsed_product_code[10];
    sscanf(payload, "product_code: %s\nquantity: %d", parsed_product_code, quantity);
    *product_code = strdup(parsed_product_code);
    return parsed_product_code;
}

const char* calculate_price(const char *yaml_payload) {
    const char *product_code;
    int quantity;

    parse_yaml_payload(yaml_payload, &product_code, &quantity);

    float price_per_item = get_product_price(product_code);
    if (price_per_item == -1.0) {
        return "Product not found";
    }

    float total_price = price_per_item * quantity;

    static char result[50];
    snprintf(result, sizeof(result), "%.2f", total_price);

    free((void*)product_code); // Free the strdup'ed memory

    return result;
}

int main() {
    const char *yaml_payload = "product_code: P001\nquantity: 3";
    printf("Total Price: %s\n", calculate_price(yaml_payload));
    return 0;
}