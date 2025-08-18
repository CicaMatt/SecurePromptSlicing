#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char key[256];
    char value[256];
} yaml_pair;

int get_price_for_product_code(const char *product_code) {
    if (strcmp(product_code, "A001") == 0)
        return 100;
    else if (strcmp(product_code, "B002") == 0)
        return 200;
    else if (strcmp(product_code, "C003") == 0)
        return 300;
    return -1; // Invalid product code
}

yaml_pair parse_yaml(const char *payload) {
    yaml_pair pair = {0};
    sscanf(payload, "%*[^:]:%255s", pair.key);
    sscanf(payload, "%*s:%255s", pair.value);
    return pair;
}

int calculate_price(const char *yaml_payload) {
    const char *product_code_key = "product_code";
    const char *quantity_key = "quantity";

    yaml_pair product_code = parse_yaml(yaml_payload);
    if (strcmp(product_code.key, product_code_key) != 0)
        return -1;

    yaml_pair quantity = parse_yaml(strstr(yaml_payload, ":") + 1);
    if (strcmp(quantity.key, quantity_key) != 0)
        return -1;

    int price_per_unit = get_price_for_product_code(product_code.value);
    if (price_per_unit == -1)
        return -1;

    int total_quantity;
    sscanf(quantity.value, "%d", &total_quantity);

    int total_price = price_per_unit * total_quantity;

    printf("product_code: %s\nquantity: %d\ntotal_price: %d\n", product_code_key, total_quantity, total_price);
    return 0;
}

int main() {
    const char *yaml_payload = "product_code:A001\nquantity:3";
    if (calculate_price(yaml_payload) == -1)
        printf("Error calculating price.\n");
    
    return 0;
}