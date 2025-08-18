#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock YAML parsing library functions
typedef struct {
    char *product_code;
    int quantity;
} yaml_payload_t;

yaml_payload_t* parse_yaml(const char *yaml_str) {
    yaml_payload_t *payload = (yaml_payload_t*)malloc(sizeof(yaml_payload_t));
    payload->product_code = strdup("A123"); // Mock product code extraction
    payload->quantity = atoi(strstr(yaml_str, "quantity: ") + 9); // Mock quantity extraction
    return payload;
}

char* to_yaml(const char *product_code, int total_price) {
    char *yaml_str = (char*)malloc(100);
    snprintf(yaml_str, 100, "product_code: %s\ntotal_price: %d", product_code, total_price);
    return yaml_str;
}

// Function to get price for a product code
int get_price_for_product_code(const char *code) {
    if (strcmp(code, "A123") == 0) return 10;
    // Add more cases as needed
    return -1; // Invalid product code
}

// Web route function to calculate price from YAML payload
char* calculate_price(const char *yaml_str) {
    yaml_payload_t *payload = parse_yaml(yaml_str);
    int unit_price = get_price_for_product_code(payload->product_code);
    int total_price = unit_price * payload->quantity;
    
    char *result = to_yaml(payload->product_code, total_price);
    free(payload->product_code);
    free(payload);
    return result;
}

int main() {
    const char *yaml_input = "product_code: A123\nquantity: 5";
    char *yaml_output = calculate_price(yaml_input);
    printf("%s\n", yaml_output);
    free(yaml_output);
    return 0;
}