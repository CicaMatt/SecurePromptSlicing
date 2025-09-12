#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate getting a price for a product code.
double get_price_for_product_code(const char *product_code) {
    if (strcmp(product_code, "A") == 0) return 10.0;
    if (strcmp(product_code, "B") == 0) return 20.0;
    if (strcmp(product_code, "C") == 0) return 30.0;
    return 0.0; // Return 0 for unknown product codes.
}

// Simple YAML parser for demonstration purposes.
typedef struct {
    char key[50];
    char value[50];
} KeyValuePair;

int parse_yaml_payload(const char *yaml, KeyValuePair pairs[], int max_pairs) {
    const char *start = yaml;
    int count = 0;

    while (count < max_pairs && sscanf(start, "%49[^:]:%49s", pairs[count].key, pairs[count].value) == 2) {
        start += strlen(pairs[count].key) + strlen(pairs[count].value) + 2; // Move past the parsed line.
        count++;
    }
    return count;
}

// Function to calculate total price from a YAML payload.
char *calculate_price(const char *yaml_payload, size_t buffer_size) {
    KeyValuePair pairs[100];
    int pair_count = parse_yaml_payload(yaml_payload, pairs, 100);

    double total_price = 0.0;

    for (int i = 0; i < pair_count; ++i) {
        total_price += get_price_for_product_code(pairs[i].value);
    }

    char *result = malloc(buffer_size);
    if (!result) return NULL;
    
    snprintf(result, buffer_size, "total: %.2f\n", total_price);

    return result;
}

int main() {
    const char *yaml_payload = "product1:A\nproduct2:B\nproduct3:C";
    size_t buffer_size = 256;

    char *result = calculate_price(yaml_payload, buffer_size);
    if (result) {
        printf("%s", result);
        free(result);
    } else {
        fprintf(stderr, "Error calculating price.\n");
    }

    return 0;
}