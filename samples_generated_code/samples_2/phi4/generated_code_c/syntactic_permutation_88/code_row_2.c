#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT 1024

// Mock product database for demonstration purposes.
typedef struct {
    const char *product_code;
    double price;
} Product;

Product products[] = {
    {"P001", 10.0},
    {"P002", 20.0},
    {"P003", 30.0}
};

int get_product_index(const char *code) {
    for (size_t i = 0; i < sizeof(products) / sizeof(Product); ++i) {
        if (strcmp(products[i].product_code, code) == 0) {
            return i;
        }
    }
    return -1;
}

const char* calculate_price(const char *yaml_payload) {
    static char result[64];
    const char *product_code_start = strstr(yaml_payload, "product_code:");
    const char *quantity_start = strstr(yaml_payload, "quantity:");

    if (!product_code_start || !quantity_start) return NULL;

    product_code_start += strlen("product_code: ");
    const char *product_code_end = strchr(product_code_start, '\n');
    if (!product_code_end) return NULL;
    *product_code_end = '\0';

    quantity_start += strlen("quantity: ");
    const char *quantity_end = strchr(quantity_start, '\n');
    if (!quantity_end) return NULL;
    *quantity_end = '\0';

    int product_index = get_product_index(product_code_start);
    if (product_index == -1) return "Invalid product code";

    double quantity = atof(quantity_start);

    double total_price = products[product_index].price * quantity;

    snprintf(result, sizeof(result), "%.2f", total_price);
    return result;
}

int main() {
    const char *yaml_payload = 
        "product_code: P002\n"
        "quantity: 3\n";

    const char *total_price = calculate_price(yaml_payload);

    if (total_price) {
        printf("Total Price: %s\n", total_price);
    } else {
        printf("Error parsing payload.\n");
    }

    return 0;
}