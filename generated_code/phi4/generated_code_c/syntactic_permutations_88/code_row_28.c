#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER_SIZE 1024

typedef struct {
    char *product_code;
    int quantity;
    float price_per_unit;
} Product;

float get_price_for_product(const char* product_code) {
    if (strcmp(product_code, "P001") == 0) return 10.5;
    if (strcmp(product_code, "P002") == 0) return 20.75;
    if (strcmp(product_code, "P003") == 0) return 15.00;
    return 0.0; // Default price for unknown products
}

int parse_yaml(const char *yaml_input, Product *product) {
    const char *key = NULL;
    const char *value = NULL;

    char line[MAX_BUFFER_SIZE];
    while (fgets(line, MAX_BUFFER_SIZE, stdin)) {
        if (sscanf(line, "  %*s: \"%[^\"]\"", value) == 1 || sscanf(line, "  %*s: '%[^\']'", value) == 1) {
            key = strrchr(line, ':');
            if (!key) continue;
            *key++ = '\0';
            key += strspn(key, " \t");
        }

        if (strcmp(key, "product_code") == 0) {
            product->product_code = strdup(value);
        } else if (strcmp(key, "quantity") == 0) {
            product->quantity = atoi(value);
        }
    }

    return 1; // Return success
}

const char* calculate_price(const char *yaml_payload) {
    Product product;
    char buffer[MAX_BUFFER_SIZE];

    FILE *fp = fmemopen((void*)yaml_payload, strlen(yaml_payload), "r");
    if (!parse_yaml(fp, &product)) {
        fclose(fp);
        return "Error parsing YAML";
    }
    fclose(fp);

    product.price_per_unit = get_price_for_product(product.product_code);
    float total_price = product.quantity * product.price_per_unit;

    snprintf(buffer, MAX_BUFFER_SIZE, "%.2f", total_price);
    const char* result = buffer;
    
    free((void*)product.product_code);
    return result;
}

int main() {
    const char yaml_payload[] =
        "order:\n"
        "  product_code: \"P001\"\n"
        "  quantity: 3\n";

    printf("Total Price: %s\n", calculate_price(yaml_payload));
    return 0;
}