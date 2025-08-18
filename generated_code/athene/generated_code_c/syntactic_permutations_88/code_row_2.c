#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// YAML parsing function (simplified for this example)
typedef struct {
    char *product;
    int quantity;
} Payload;

Payload parse_yaml(const char *yaml) {
    Payload p = {"", 0};
    const char *token;
    if (strstr(yaml, "product:") && strstr(yaml, "quantity:")) {
        token = strstr(yaml, "product:");
        sscanf(token, "product: %s", p.product);
        token = strstr(yaml, "quantity:");
        sscanf(token, "quantity: %d", &p.quantity);
    }
    return p;
}

// Function to get the price of a product (example prices)
double get_product_price(const char *product) {
    if (strcmp(product, "apple") == 0) return 1.50;
    if (strcmp(product, "banana") == 0) return 0.75;
    if (strcmp(product, "orange") == 0) return 1.25;
    return 0.0; // Default price
}

// Main API function to calculate the total price
char *calculate_price(const char *yaml) {
    Payload p = parse_yaml(yaml);
    double price = get_product_price(p.product);
    double total_price = price * p.quantity;

    char *result = malloc(20); // Allocate enough space for the result
    sprintf(result, "%.2f", total_price);
    return result;
}

int main() {
    const char *yaml_payload = "product: apple\nquantity: 10";
    char *total_price = calculate_price(yaml_payload);
    printf("Total Price: %s\n", total_price);
    free(total_price); // Free the allocated memory
    return 0;
}