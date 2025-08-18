#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char key[256];
    int value;
} KeyValuePair;

int get_price_for_product_code(const char *product_code) {
    if (strcmp(product_code, "P001") == 0) return 100;
    if (strcmp(product_code, "P002") == 0) return 200;
    if (strcmp(product_code, "P003") == 0) return 300;
    return -1; // Product code not found
}

int extract_int_from_string(const char *str, const char *key) {
    char buffer[256];
    snprintf(buffer, sizeof(buffer), "%s: %d", key, atoi(strchr(strchr(str, '\n') + 2, ':')));
    return atoi(buffer);
}

char* calculate_price(char *yaml_payload) {
    static char result[256];
    KeyValuePair kv_pairs[3] = {
        {"product_code", extract_int_from_string(yaml_payload, "product_code")},
        {"quantity", extract_int_from_string(yaml_payload, "quantity")}
    };

    for (int i = 0; i < 2; i++) {
        if (kv_pairs[i].value == -1) {
            snprintf(result, sizeof(result), "error: %s not found", kv_pairs[i].key);
            return result;
        }
    }

    int price_per_item = get_price_for_product_code(kv_pairs[0].value ? &kv_pairs[0].key : "");
    if (price_per_item == -1) {
        snprintf(result, sizeof(result), "error: Invalid product code");
        return result;
    }

    int total_price = price_per_item * kv_pairs[1].value;
    snprintf(result, sizeof(result), "total_price: %d", total_price);
    return result;
}

int main() {
    char yaml_payload[] =
        "product_code: 1001\n"
        "quantity: 2";
        
    printf("Result YAML:\n%s\n", calculate_price(yaml_payload));
    return 0;
}