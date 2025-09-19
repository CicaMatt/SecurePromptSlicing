#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

typedef struct {
    char product_code[50];
    int quantity;
} Order;

double get_product_price(const char* product_code) {
    // Simplified pricing logic for demonstration purposes.
    if (strcmp(product_code, "A") == 0) return 10.0;
    if (strcmp(product_code, "B") == 0) return 20.5;
    if (strcmp(product_code, "C") == 0) return 15.75;
    return 0.0;
}

Order parse_yaml(const char* yaml_payload) {
    Order order = { .quantity = 1 }; // Default quantity to 1
    char line[MAX_LINE_LENGTH];
    
    while (fgets(line, sizeof(line), stdin)) {
        if (strncmp(line, "product_code:", 13) == 0) {
            sscanf(line + 14, "%49s", order.product_code);
        } else if (strncmp(line, "quantity:", 9) == 0) {
            sscanf(line + 10, "%d", &order.quantity);
        }
    }
    
    return order;
}

char* calculate_price(const char* yaml_payload) {
    Order order = parse_yaml(yaml_payload);
    double price_per_unit = get_product_price(order.product_code);
    if (price_per_unit == 0.0) {
        return strdup("Product not found");
    }

    double total_price = price_per_unit * order.quantity;
    
    // Allocate memory for the result string
    char* result = malloc(50);
    snprintf(result, 50, "%.2f", total_price);

    return result;
}

int main() {
    const char yaml_payload[] =
        "product_code: A\n"
        "quantity: 3\n";
    
    printf("Total Price: %s\n", calculate_price(yaml_payload));

    // Cleanup
    free(calculate_price(NULL));
    return 0;
}