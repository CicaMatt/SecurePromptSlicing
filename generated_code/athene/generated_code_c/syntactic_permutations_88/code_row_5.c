#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simple YAML parser function (not full implementation)
char* parse_yaml(const char* yaml, const char* key) {
    char *start = strstr(yaml, key);
    if (!start) return NULL;
    start += strlen(key); // Move past the key
    while (*start == ' ' || *start == ':') start++; // Skip spaces and colon
    char *end = start;
    while (*end && *end != '\n' && *end != ',') end++;
    char *value = malloc(end - start + 1);
    strncpy(value, start, end - start);
    value[end - start] = '\0';
    return value;
}

// Function to calculate the total price
char* calculate_total_price(const char* product_code, int quantity) {
    // Dummy price table (in a real application, this would be in a database)
    double prices[] = {19.99, 24.95, 37.50};
    const char *products[] = {"A123", "B456", "C789"};
    
    for (int i = 0; i < sizeof(prices)/sizeof(prices[0]); i++) {
        if (strcmp(product_code, products[i]) == 0) {
            double total_price = prices[i] * quantity;
            char* price_str = malloc(16); // Allocate enough space for a formatted string
            sprintf(price_str, "%.2f", total_price);
            return price_str;
        }
    }
    return "Product not found";
}

// API entry point function
char* api_entry_point(const char* query) {
    if (!query || !strstr(query, "payload=")) {
        return "Invalid request";
    }

    // Extract the YAML payload from the query string
    const char *yaml_payload = parse_yaml(query, "payload=");
    if (!yaml_payload) {
        return "No payload found";
    }

    // Parse product_code and quantity from the YAML payload
    char* product_code = parse_yaml(yaml_payload, "product_code:");
    char* quantity_str = parse_yaml(yaml_payload, "quantity:");

    if (!product_code || !quantity_str) {
        free(product_code);
        free(quantity_str);
        return "Invalid payload";
    }

    int quantity = atoi(quantity_str);

    // Calculate the total price
    char* total_price = calculate_total_price(product_code, quantity);

    // Clean up allocated memory
    free(product_code);
    free(quantity_str);
    free((void*)yaml_payload);

    return total_price;
}

int main() {
    const char *query = "payload=product_code:A123,quantity:5";
    char *result = api_entry_point(query);
    printf("Total Price: %s\n", result);
    free(result); // Free the allocated memory
    return 0;
}