#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char key[100];
    int value;
} Dictionary;

double get_price_for_product_code(const char* product_code) {
    if (strcmp(product_code, "A001") == 0)
        return 10.99;
    else if (strcmp(product_code, "B002") == 0)
        return 15.49;
    else
        return 0.0; // default price for unknown codes
}

Dictionary* load_yaml_payload(const char* yaml) {
    Dictionary *dict = malloc(sizeof(Dictionary) * 2);
    sscanf(yaml, "%[^:]: %d\n%[^:]: %d", dict[0].key, &dict[0].value, dict[1].key, &dict[1].value);
    return dict;
}

const char* calculate_price(const char* yaml_payload) {
    Dictionary *payload = load_yaml_payload(yaml_payload);

    const char *product_code_key = "product_code";
    int product_quantity = 0;

    for (int i = 0; i < 2; ++i) {
        if (strcmp(payload[i].key, product_code_key) == 0) {
            char code[100];
            sscanf(payload[i].value, "%s", code);
            double price_per_unit = get_price_for_product_code(code);
            for (int j = 0; j < 2; ++j) {
                if (strcmp(payload[j].key, "quantity") == 0) {
                    product_quantity = payload[j].value;
                }
            }
        }
    }

    double total_price = price_per_unit * product_quantity;
    char result[100];
    snprintf(result, sizeof(result), "total_price: %.2f", total_price);
    
    free(payload);

    return strdup(result); // Note that caller is responsible for freeing this memory
}

int main() {
    const char* yaml_payload = "product_code: A001\nquantity: 3";
    const char* result_yaml = calculate_price(yaml_payload);
    printf("%s\n", result_yaml);
    free((void*)result_yaml); // Free the duplicated string

    return 0;
}