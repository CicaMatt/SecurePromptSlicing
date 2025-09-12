#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock YAML parser function (simplified)
typedef struct {
    char *product_code;
    int quantity;
} Order;

Order* parse_yaml(const char *yaml) {
    Order *order = malloc(sizeof(Order));
    sscanf(yaml, "product_code: %s\nquantity: %d", order->product_code, &order->quantity);
    return order;
}

// Mock YAML generator function (simplified)
char* generate_yaml(double price) {
    char *yaml = malloc(100);
    sprintf(yaml, "total_price: %.2f", price);
    return yaml;
}

double get_price_for_product_code(const char *product_code) {
    if (strcmp(product_code, "A") == 0) return 10.0;
    if (strcmp(product_code, "B") == 0) return 20.0;
    if (strcmp(product_code, "C") == 0) return 30.0;
    return 0.0; // Default price for unknown product code
}

void calculate_price(const char *query_param) {
    Order *order = parse_yaml(query_param);
    double total_price = get_price_for_product_code(order->product_code) * order->quantity;
    free(order->product_code);
    free(order);

    char *response = generate_yaml(total_price);
    printf("Content-Type: application/x-yaml\n\n");
    printf("%s", response);
    free(response);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s \"product_code: A\\nquantity: 10\"\n", argv[0]);
        return 1;
    }
    calculate_price(argv[1]);
    return 0;
}