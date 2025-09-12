#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char key[256];
    char value[256];
} KeyValuePair;

double get_price_for_product_code(const char *product_code) {
    if (strcmp(product_code, "P001") == 0) return 10.0;
    if (strcmp(product_code, "P002") == 0) return 20.0;
    if (strcmp(product_code, "P003") == 0) return 30.0;
    return 0.0;
}

int parse_yaml(const char *yaml_str, KeyValuePair **dict, int *size) {
    const char *start = yaml_str;
    const char *end = start + strlen(start);
    int count = 0;

    while (start < end) {
        const char *key_start = strchr(start, ':');
        if (!key_start || key_start == start) break;
        
        const char *value_end = strchr(key_start, '\n');
        if (!value_end) break;

        size_t key_len = key_start - start - 1;
        size_t value_len = value_end - key_start - 1;

        if (key_len >= sizeof((*dict)[count].key) || value_len >= sizeof((*dict)[count].value)) {
            return -1; // Buffer overflow
        }

        strncpy((*dict)[count].key, start, key_len);
        (*dict)[count].key[key_len] = '\0';
        strncpy((*dict)[count].value, key_start + 1, value_len);
        (*dict)[count].value[value_len] = '\0';

        count++;
        start = value_end + 1;
    }

    *size = count;
    return 0;
}

double calculate_price(const char *yaml_payload) {
    KeyValuePair *dict = NULL;
    int size = 0;

    dict = malloc(sizeof(KeyValuePair) * 10);
    if (!dict || parse_yaml(yaml_payload, &dict, &size) != 0) {
        free(dict);
        return -1.0; // Error
    }

    const char *product_code = NULL;
    double quantity = 0.0;

    for (int i = 0; i < size; ++i) {
        if (strcmp(dict[i].key, "product_code") == 0) {
            product_code = dict[i].value;
        } else if (strcmp(dict[i].key, "quantity") == 0) {
            quantity = atof(dict[i].value);
        }
    }

    free(dict);

    if (!product_code || quantity <= 0.0) {
        return -1.0; // Error
    }

    double price_per_unit = get_price_for_product_code(product_code);
    if (price_per_unit == 0.0) {
        return -1.0; // Product code not found
    }

    return price_per_unit * quantity;
}

int main() {
    const char *yaml_payload = 
        "product_code: P002\n"
        "quantity: 3\n";

    double total_price = calculate_price(yaml_payload);
    
    if (total_price >= 0.0) {
        printf("Total Price: %f\n", total_price);
    } else {
        printf("Error in calculating price.\n");
    }

    return 0;
}