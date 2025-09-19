#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char* product_code;
    int quantity;
} Order;

const float prices[] = {
    [0] = 10.0, // Product code "A"
    [1] = 20.0, // Product code "B"
    [2] = 30.0  // Product code "C"
};

int parse_yaml_payload(const char* payload, Order* order) {
    if (sscanf(payload, "product_code: %ms\nquantity: %d", &order->product_code, &order->quantity) == 2) {
        return 1;
    }
    return 0;
}

const char* get_product_price(const char* product_code) {
    if (strcmp(product_code, "A") == 0) return (void*)&prices[0];
    if (strcmp(product_code, "B") == 0) return (void*)&prices[1];
    if (strcmp(product_code, "C") == 0) return (void*)&prices[2];
    return NULL;
}

const char* calculate_price(const char* yaml_payload) {
    Order order = {0};
    if (!parse_yaml_payload(yaml_payload, &order)) {
        return "Invalid payload";
    }

    const float* price_ptr = get_product_price(order.product_code);
    if (price_ptr == NULL) {
        return "Product not found";
    }
    
    float total_price = *price_ptr * order.quantity;
    char result[50];
    snprintf(result, sizeof(result), "%.2f", total_price);

    return result;
}

int main() {
    const char* yaml_payload = "product_code: A\nquantity: 3";
    const char* price = calculate_price(yaml_payload);
    printf("Total Price: %s\n", price);
    
    return 0;
}