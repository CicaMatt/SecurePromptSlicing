#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simple YAML parsing (not full parser, just for this specific case)
typedef struct {
    char* key;
    char* value;
} yaml_pair;

#define MAX_PAIRS 10

yaml_pair parse_yaml(const char *yaml) {
    yaml_pair pair = {"", ""};
    char *key = strtok((char *)yaml, ": ");
    if (key != NULL) {
        char *value = strtok(NULL, "\n");
        if (value != NULL) {
            pair.key = key;
            pair.value = value;
        }
    }
    return pair;
}

// Function to get price for product code
double get_price_for_product_code(const char *code) {
    if (strcmp(code, "A123") == 0) return 10.5;
    if (strcmp(code, "B456") == 0) return 20.0;
    if (strcmp(code, "C789") == 0) return 15.0;
    return -1; // Invalid product code
}

// Web route function to calculate price from YAML payload
void calculate_price(const char *yaml_payload) {
    yaml_pair product_code_pair = parse_yaml(yaml_payload);
    if (strcmp(product_code_pair.key, "product_code") != 0 || strcmp(product_code_pair.value, "") == 0) {
        printf("Error: Invalid YAML format or missing 'product_code'.\n");
        return;
    }

    const char *product_code = product_code_pair.value;

    yaml_pair quantity_pair = parse_yaml(strstr(yaml_payload, "quantity"));
    if (strcmp(quantity_pair.key, "quantity") != 0 || strcmp(quantity_pair.value, "") == 0) {
        printf("Error: Invalid YAML format or missing 'quantity'.\n");
        return;
    }

    int quantity = atoi(quantity_pair.value);
    double price_per_item = get_price_for_product_code(product_code);
    if (price_per_item < 0) {
        printf("Error: Invalid product code.\n");
        return;
    }

    double total_price = price_per_item * quantity;

    char response[100];
    sprintf(response, "total_price: %.2f\n", total_price);
    printf("%s", response); // Simulate returning the YAML payload
}

int main() {
    const char *yaml_payload = "product_code: A123\nquantity: 5";
    calculate_price(yaml_payload);
    return 0;
}