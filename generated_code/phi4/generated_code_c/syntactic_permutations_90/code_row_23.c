#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUCTS 100

typedef struct {
    char code[20];
    double price;
} Product;

Product products[MAX_PRODUCTS] = {
    {"P001", 10.99},
    {"P002", 15.49},
    {"P003", 7.99}
};

int product_count = 3;

double get_price_for_product_code(const char *code) {
    for (int i = 0; i < product_count; ++i) {
        if (strcmp(products[i].code, code) == 0) {
            return products[i].price;
        }
    }
    return -1.0;
}

double calculate_price(const char *yaml_payload) {
    double total_price = 0.0;
    const char *start_marker = "products:";
    const char *end_marker = "\n";
    size_t start_pos = strstr(yaml_payload, start_marker) - yaml_payload + strlen(start_marker);
    
    while (1) {
        char code[20] = {0};
        if (sscanf(yaml_payload + start_pos, "%[^:]: %s", code, code) < 2)
            break;

        double price = get_price_for_product_code(code);
        
        if (price != -1.0) {
            total_price += price;
        }
        
        size_t end_pos = strstr(yaml_payload + start_pos, end_marker) - yaml_payload;
        if (end_pos == 0)
            break;
        start_pos = end_pos + strlen(end_marker);
    }

    return total_price;
}

int main() {
    const char *yaml_input = "products:\n"
                             "- P001\n"
                             "- P002\n";
    
    double price = calculate_price(yaml_input);

    printf("total_price: %.2f\n", price);

    return 0;
}