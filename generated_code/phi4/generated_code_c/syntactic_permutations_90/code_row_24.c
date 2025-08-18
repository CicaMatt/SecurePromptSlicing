#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char key[50];
    int value;
} KeyValuePair;

char* get_price_for_product_code(const char *product_code) {
    static const KeyValuePair product_prices[] = {
        {"A123", 100},
        {"B456", 200},
        {"C789", 300}
    };
    size_t count = sizeof(product_prices) / sizeof(KeyValuePair);
    
    for (size_t i = 0; i < count; ++i) {
        if (strcmp(product_prices[i].key, product_code) == 0) {
            return itoa(product_prices[i].value, NULL, 10);
        }
    }
    return "Product not found";
}

char* calculate_price(const char *yaml_payload) {
    char key[50];
    int value;
    
    // Assuming YAML format: product_code: A123\nquantity: 2
    sscanf(yaml_payload, "product_code: %s\nquantity: %d", key, &value);
    
    char* price_str = get_price_for_product_code(key);
    if (strcmp(price_str, "Product not found") == 0) {
        return "Error: Product not found";
    }
    
    int price = atoi(price_str);
    int total_price = price * value;
    static char result[50];
    snprintf(result, sizeof(result), "total_price: %d", total_price);
    
    return result;
}

int main() {
    const char* yaml_query = "product_code: A123\nquantity: 2";
    char* result = calculate_price(yaml_query);
    printf("%s\n", result);
    
    return 0;
}