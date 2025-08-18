#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simple YAML parsing function for demonstration purposes
typedef struct {
    char *product_code;
    int quantity;
} ProductRequest;

ProductRequest parse_yaml(const char *yaml_payload) {
    ProductRequest request = {NULL, 0};
    const char *start_product_key = "product_code: ";
    const char *start_quantity_key = "quantity: ";

    for (const char *line = yaml_payload; line && *line; line++) {
        if (strncmp(line, start_product_key, strlen(start_product_key)) == 0) {
            request.product_code = strdup(line + strlen(start_product_key));
        } else if (strncmp(line, start_quantity_key, strlen(start_quantity_key)) == 0) {
            sscanf(line + strlen(start_quantity_key), "%d", &request.quantity);
        }
    }

    return request;
}

// Example product prices
typedef struct {
    char *code;
    double price;
} Product;

double get_product_price(const char *product_code, Product products[], size_t num_products) {
    for (size_t i = 0; i < num_products; ++i) {
        if (strcmp(products[i].code, product_code) == 0) {
            return products[i].price;
        }
    }
    return -1.0; // Product not found
}

const char* calculate_price(const char *yaml_payload) {
    static char result[64];

    ProductRequest request = parse_yaml(yaml_payload);

    if (request.product_code == NULL || request.quantity <= 0) {
        snprintf(result, sizeof(result), "Invalid request");
        free(request.product_code);
        return result;
    }

    // Example products
    Product products[] = {
        {"A123", 10.5},
        {"B456", 7.2},
        {"C789", 15.0}
    };
    size_t num_products = sizeof(products) / sizeof(products[0]);

    double price_per_unit = get_product_price(request.product_code, products, num_products);
    if (price_per_unit < 0) {
        snprintf(result, sizeof(result), "Product not found");
    } else {
        snprintf(result, sizeof(result), "%.2f", price_per_unit * request.quantity);
    }

    free(request.product_code);
    return result;
}

int main() {
    const char *yaml_payload = 
        "product_code: A123\n"
        "quantity: 3\n";

    printf("Total Price: %s\n", calculate_price(yaml_payload));
    return 0;
}