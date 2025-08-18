#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PAYLOAD_SIZE 1024

typedef struct {
    char key[50];
    char value[100];
} KeyValue;

int get_price_for_product(const char* product) {
    if (strcmp(product, "apple") == 0) return 1;
    if (strcmp(product, "banana") == 0) return 2;
    if (strcmp(product, "orange") == 0) return 3;
    return -1; // Product not found
}

int parse_yaml_payload(const char* payload, KeyValue* kv_pairs, int max_pairs) {
    const char* key_value_delim = ": ";
    char* line = strtok((char*)payload, "\n");
    int count = 0;

    while (line != NULL && count < max_pairs) {
        char* value = strchr(line, ':');
        if (value == NULL) break;
        *value = '\0';
        strcpy(kv_pairs[count].key, line);
        strcpy(kv_pairs[count].value, ++value);
        line = strtok(NULL, "\n");
        count++;
    }
    return count;
}

int calculate_price(const char* yaml_payload) {
    KeyValue kv_pairs[10];
    int num_pairs = parse_yaml_payload(yaml_payload, kv_pairs, 10);

    const char* product_key = "product";
    const char* quantity_key = "quantity";

    int product_index = -1;
    int quantity_index = -1;

    for (int i = 0; i < num_pairs; ++i) {
        if (strcmp(kv_pairs[i].key, product_key) == 0) product_index = i;
        if (strcmp(kv_pairs[i].key, quantity_key) == 0) quantity_index = i;
    }

    if (product_index == -1 || quantity_index == -1) return -1; // Missing keys

    int price_per_unit = get_price_for_product(kv_pairs[product_index].value);
    if (price_per_unit == -1) return -1; // Invalid product

    int quantity = atoi(kv_pairs[quantity_index].value);
    return price_per_unit * quantity;
}

void handle_request(const char* yaml_payload) {
    int total_price = calculate_price(yaml_payload);

    if (total_price == -1) {
        printf("Error: Unable to calculate price\n");
        return;
    }

    printf("---\ntotal_price: %d\n", total_price);
}

int main() {
    const char* yaml_payload = 
        "product: apple\n"
        "quantity: 5";

    handle_request(yaml_payload);

    return 0;
}