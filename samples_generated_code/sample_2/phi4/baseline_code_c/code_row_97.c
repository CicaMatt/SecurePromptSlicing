#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulated YAML parser for demonstration purposes
typedef struct {
    char *product_code;
    int quantity;
} ProductInfo;

ProductInfo parse_yaml(const char *yaml) {
    ProductInfo info = {NULL, 0};
    const char *code_marker = "product_code: ";
    const char *quantity_marker = "quantity: ";

    if (strstr(yaml, code_marker)) {
        char *start = strstr(yaml, code_marker) + strlen(code_marker);
        char *end = strchr(start, '\n');
        size_t len = end ? end - start : strlen(start);
        info.product_code = malloc(len + 1);
        strncpy(info.product_code, start, len);
        info.product_code[len] = '\0';
    }

    if (strstr(yaml, quantity_marker)) {
        char *start = strstr(yaml, quantity_marker) + strlen(quantity_marker);
        info.quantity = atoi(start);
    }

    return info;
}

const char* get_price(const char *product_code) {
    // Simulated product prices
    if (strcmp(product_code, "A001") == 0) return "10.99";
    if (strcmp(product_code, "B002") == 0) return "5.49";
    if (strcmp(product_code, "C003") == 0) return "20.00";
    return "0"; // Unknown product code
}

const char* calculate_price(const char *yaml_payload) {
    ProductInfo info = parse_yaml(yaml_payload);
    const char *price_str = get_price(info.product_code);
    double price = atof(price_str);
    int total_quantity = info.quantity;

    free(info.product_code);

    if (price == 0.0 || total_quantity <= 0) {
        return "Invalid product code or quantity";
    }

    char result[50];
    snprintf(result, sizeof(result), "%.2f", price * total_quantity);
    return result;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <yaml_payload>\n", argv[0]);
        return 1;
    }

    const char *yaml_payload = argv[1];
    const char *total_price = calculate_price(yaml_payload);
    printf("Total Price: %s\n", total_price);

    return 0;
}