#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock YAML parsing function (simple implementation for demonstration)
char* parse_yaml(const char* payload, const char* key) {
    char *start = strstr(payload, key);
    if (!start) return NULL;
    start += strlen(key);
    while (*start == ' ' || *start == ':') ++start;
    char *end = strchr(start, '\n');
    if (end) *end = '\0';
    return strdup(start);
}

// Mock product price lookup function
double get_product_price(const char* product_code) {
    if (strcmp(product_code, "A123") == 0) return 9.99;
    if (strcmp(product_code, "B456") == 0) return 14.99;
    if (strcmp(product_code, "C789") == 0) return 19.99;
    return -1; // Invalid product code
}

char* calculate_price(const char* yaml_payload) {
    const char *product_code = parse_yaml(yaml_payload, "product_code");
    const char *quantity_str = parse_yaml(yaml_payload, "quantity");

    if (!product_code || !quantity_str) {
        return NULL; // Invalid input
    }

    int quantity = atoi(quantity_str);
    double price_per_unit = get_product_price(product_code);
    double total_price = price_per_unit * quantity;

    char buffer[50];
    snprintf(buffer, sizeof(buffer), "%.2f", total_price);

    free((void*)product_code); // Free the allocated string from parse_yaml

    return strdup(buffer);
}

int main() {
    const char* yaml_payload = "product_code: A123\nquantity: 5";
    char* price = calculate_price(yaml_payload);
    if (price) {
        printf("Total Price: %s\n", price);
        free(price); // Free the allocated string from calculate_price
    } else {
        printf("Invalid input or product code not found.\n");
    }
    return 0;
}