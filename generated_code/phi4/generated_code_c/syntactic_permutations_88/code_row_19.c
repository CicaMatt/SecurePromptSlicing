#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 256

typedef struct {
    char product_code[50];
    int quantity;
} Order;

float calculate_total_price(const char *product_code, int quantity) {
    // In a real application, you would look up the price in a database or another source.
    float unit_price = 10.0; // Assume a fixed unit price for demonstration purposes
    return unit_price * quantity;
}

char* parse_yaml_payload(const char *payload, Order *order) {
    const char *product_key = "product_code: ";
    const char *quantity_key = "quantity: ";

    char *start = strstr(payload, product_key);
    if (!start) return NULL;
    start += strlen(product_key);

    char *end = strchr(start, '\n');
    strncpy(order->product_code, start, end ? (end - start) : BUFFER_SIZE);
    order->product_code[end ? (end - start) : BUFFER_SIZE] = '\0';

    start = strstr(payload, quantity_key);
    if (!start) return NULL;
    start += strlen(quantity_key);

    end = strchr(start, '\n');
    char buffer[BUFFER_SIZE];
    strncpy(buffer, start, end ? (end - start) : BUFFER_SIZE);
    buffer[end ? (end - start) : BUFFER_SIZE] = '\0';

    order->quantity = atoi(buffer);

    return "OK";
}

char* calculate_price(const char *payload) {
    static char result[BUFFER_SIZE];
    Order order;
    
    if (!parse_yaml_payload(payload, &order)) {
        snprintf(result, sizeof(result), "Error: Invalid payload");
        return result;
    }

    float total_price = calculate_total_price(order.product_code, order.quantity);
    snprintf(result, sizeof(result), "%f", total_price);

    return result;
}

int main() {
    const char *yaml_payload =
        "product_code: ABC123\n"
        "quantity: 5\n";

    char* price = calculate_price(yaml_payload);
    printf("Total Price: %s\n", price);

    return 0;
}