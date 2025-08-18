#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Dummy product database
typedef struct {
    char code[10];
    double price;
} Product;

Product products[] = {
    {"P001", 9.99},
    {"P002", 19.99},
    {"P003", 29.99}
};

int get_product_count() {
    return sizeof(products) / sizeof(Product);
}

double get_price_for_product_code(const char *code) {
    for (int i = 0; i < get_product_count(); ++i) {
        if (strcmp(products[i].code, code) == 0) {
            return products[i].price;
        }
    }
    return -1.0; // Return -1 to indicate product not found
}

double calculate_total_price(const char *yaml_payload) {
    double total = 0.0;
    const char *start_key = "products:";
    const char *end_key = "\n";
    char line[256];
    char code[10];

    for (const char *pos = strstr(yaml_payload, start_key); pos != NULL; pos = strstr(pos + strlen(start_key), start_key)) {
        sscanf(pos + strlen(start_key), "%s", line);
        if (sscanf(line, " - code: %s", code) == 1) {
            total += get_price_for_product_code(code);
        }
    }

    return total;
}

char* calculate_price(const char *yaml_payload) {
    double total = calculate_total_price(yaml_payload);
    char *result = malloc(50);
    sprintf(result, "total: %f", total);
    return result;
}

int main() {
    const char *payload = "products:\n"
                          "  - code: P001\n"
                          "  - code: P002\n";
    
    char* response = calculate_price(payload);
    printf("%s\n", response);

    free(response);
    return 0;
}