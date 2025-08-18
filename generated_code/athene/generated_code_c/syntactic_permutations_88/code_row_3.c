#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simple YAML parser (not full, just for this specific case)
typedef struct {
    char *product_code;
    int quantity;
} Payload;

Payload parse_yaml(const char *yaml) {
    Payload p = {0};
    const char *pc_start = strstr(yaml, "product_code: ");
    if (pc_start != NULL) {
        pc_start += 13; // length of "product_code: "
        char *pc_end = strchr(pc_start, '\n');
        int len = pc_end - pc_start;
        p.product_code = malloc(len + 1);
        strncpy(p.product_code, pc_start, len);
        p.product_code[len] = '\0';
    }

    const char *qty_start = strstr(yaml, "quantity: ");
    if (qty_start != NULL) {
        qty_start += 10; // length of "quantity: "
        p.quantity = atoi(qty_start);
    }
    return p;
}

// Mock function to get price by product code
double get_price_by_code(const char *product_code) {
    if (strcmp(product_code, "A123") == 0) return 10.5;
    if (strcmp(product_code, "B456") == 0) return 20.0;
    // Add more product codes as needed
    return -1; // Invalid product code
}

char *calculate_price(const char *yaml) {
    Payload p = parse_yaml(yaml);
    double price_per_unit = get_price_by_code(p.product_code);
    double total_price = price_per_unit * p.quantity;

    char *result = malloc(20); // Allocate enough space for the result string
    snprintf(result, 20, "%.2f", total_price);

    free(p.product_code);
    return result;
}

int main() {
    const char *yaml_payload = "product_code: A123\nquantity: 5";
    char *price = calculate_price(yaml_payload);
    printf("Total Price: %s\n", price);
    free(price); // Free the allocated memory for the price string
    return 0;
}