#include <stdio.h>
#include <string.h>

typedef struct {
    char key[50];
    int value;
} KeyValuePair;

float get_price_for_product_code(const char *product_code) {
    if (strcmp(product_code, "P001") == 0) return 10.5;
    if (strcmp(product_code, "P002") == 0) return 20.0;
    if (strcmp(product_code, "P003") == 0) return 15.75;
    return 0.0; // Default price for unknown product codes
}

int parse_yaml(const char *yaml_payload, KeyValuePair keys[], int max_keys) {
    const char *token = strtok((char *)yaml_payload, "\n");
    int count = 0;

    while (token != NULL && count < max_keys) {
        if (sscanf(token, "%49[^:]: %d", keys[count].key, &keys[count].value) == 2) {
            count++;
        }
        token = strtok(NULL, "\n");
    }

    return count;
}

float calculate_price(const char *yaml_payload) {
    KeyValuePair keys[10];
    int key_count = parse_yaml(yaml_payload, keys, 10);

    const char *product_code_key = "product_code";
    const char *quantity_key = "quantity";

    const char *product_code = NULL;
    int quantity = 0;

    for (int i = 0; i < key_count; ++i) {
        if (strcmp(keys[i].key, product_code_key) == 0) {
            product_code = keys[i].key;
        } else if (strcmp(keys[i].key, quantity_key) == 0) {
            quantity = keys[i].value;
        }
    }

    if (!product_code || quantity <= 0) return 0.0;

    float price_per_unit = get_price_for_product_code(product_code);
    return price_per_unit * quantity;
}

void generate_yaml_response(float total_price, char *response, size_t response_size) {
    snprintf(response, response_size, "total_price: %.2f\n", total_price);
}

int main() {
    const char *yaml_payload = "product_code: P001\ntotal_quantity: 3";
    float price = calculate_price(yaml_payload);

    char response[256];
    generate_yaml_response(price, response, sizeof(response));

    printf("%s", response);

    return 0;
}