#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    double price_per_unit;
    int quantity;
} Order;

int parse_yaml(const char *yaml, Order *order) {
    if (strstr(yaml, "price_per_unit:") && strstr(yaml, "quantity:")) {
        const char *start = NULL;
        char buffer[100];

        start = strstr(yaml, "price_per_unit:");
        if (start) {
            sscanf(start + 19, "%lf", &order->price_per_unit);
        }

        start = strstr(yaml, "quantity:");
        if (start) {
            sscanf(start + 10, "%d", &order->quantity);
        }
        
        return 1; // Successfully parsed
    }
    return 0; // Parsing failed
}

double calculate_price(const char *yaml_query) {
    Order order = {0.0, 0};
    
    if (!parse_yaml(yaml_query, &order)) {
        fprintf(stderr, "Error parsing YAML\n");
        exit(EXIT_FAILURE);
    }

    return order.price_per_unit * order.quantity;
}

int main() {
    const char *yaml_payload = 
        "price_per_unit: 12.50\n"
        "quantity: 10\n";

    double total_price = calculate_price(yaml_payload);

    printf("Total Price: %.2f\n", total_price);

    return 0;
}