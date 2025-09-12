#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate getting price for a product code
double get_price_for_product_code(const char *product_code) {
    if (strcmp(product_code, "A123") == 0) return 10.5;
    if (strcmp(product_code, "B456") == 0) return 20.0;
    return -1; // Error code for invalid product
}

// Simplified YAML parser and generator functions
typedef struct {
    char *key;
    double value;
} YamlPair;

YamlPair parse_yaml(const char *yaml_str) {
    YamlPair pair = {"", 0};
    char *token = strtok((char *)yaml_str, ": ");
    if (token != NULL) {
        pair.key = strdup(token);
        token = strtok(NULL, "\n");
        if (token != NULL) {
            pair.value = atof(token);
        }
    }
    return pair;
}

char *generate_yaml(const char *key, double value) {
    int len = strlen(key) + 20; // Estimate length for the string
    char *yaml_str = malloc(len);
    snprintf(yaml_str, len, "%s: %.2f", key, value);
    return yaml_str;
}

// Web route function to calculate price from YAML payload
char *calculate_price(const char *query_param) {
    YamlPair product_code_pair = parse_yaml(query_param);
    double quantity = 1.0; // Default quantity

    if (strcmp(product_code_pair.key, "product_code") == 0) {
        const char *yaml_str = strstr(query_param, "quantity:");
        if (yaml_str != NULL) {
            YamlPair quantity_pair = parse_yaml(yaml_str);
            if (strcmp(quantity_pair.key, "quantity") == 0) {
                quantity = quantity_pair.value;
            }
        }

        double price_per_unit = get_price_for_product_code(product_code_pair.key);
        double total_price = price_per_unit * quantity;

        char *response = generate_yaml("total_price", total_price);
        free(product_code_pair.key); // Free allocated memory
        return response;
    } else {
        return generate_yaml("error", -1.0);
    }
}

int main() {
    const char *query_param = "product_code: A123\nquantity: 5";
    char *result = calculate_price(query_param);
    printf("%s\n", result);
    free(result); // Free allocated memory
    return 0;
}