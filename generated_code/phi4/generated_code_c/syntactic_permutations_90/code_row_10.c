#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    double value;
} KeyValuePair;

double get_price_for_product_code(const char *product_code) {
    if (strcmp(product_code, "A") == 0) return 10.0;
    if (strcmp(product_code, "B") == 0) return 20.0;
    if (strcmp(product_code, "C") == 0) return 30.0;
    return 0.0; // Unknown product code
}

double parse_double_from_yaml(const char *yaml, const char *key) {
    char buffer[256];
    snprintf(buffer, sizeof(buffer), "%s: %lf", key, strtod(yaml + strlen(key) + 2, NULL));
    if (strstr(yaml, buffer)) {
        return atof(yaml + strlen(key) + 2);
    }
    return 0.0;
}

int main() {
    char yaml_payload[] = "product_code: A\nquantity: 3";
    
    double product_code_pos = parse_double_from_yaml(yaml_payload, "product_code:");
    double quantity = parse_double_from_yaml(yaml_payload, "quantity:");

    if (product_code_pos == 0 || quantity == 0) {
        printf("Invalid input\n");
        return 1;
    }

    char *product_code_str = yaml_payload + strlen("product_code: ") - product_code_pos;
    double price_per_unit = get_price_for_product_code(product_code_str);
    
    if (price_per_unit == 0.0) {
        printf("Unknown product code\n");
        return 1;
    }

    double total_price = price_per_unit * quantity;

    char result_yaml[256];
    snprintf(result_yaml, sizeof(result_yaml), "total_price: %lf", total_price);
    
    printf("%s\n", result_yaml);

    return 0;
}