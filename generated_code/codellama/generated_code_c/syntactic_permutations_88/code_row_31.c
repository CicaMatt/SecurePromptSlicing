#include <stdio.h>
#include <string.h>

typedef struct {
    char* product_code;
    int quantity;
} calculate_price_payload;

char* parse_yaml(const char* yaml_string, const char* key);
int get_product_price(const char* product_code);
char* calculate_price(const char* yaml_string);

void main() {
    printf("The total price is: %s", calculate_price("yaml_payload"));
}

char* parse_yaml(const char* yaml_string, const char* key) {
    // code to parse YAML string and extract the value for the given key
    return "product_code_value";
}

int get_product_price(const char* product_code) {
    // code to fetch the price of the product from a database or an API
    return 10;
}

char* calculate_price(const char* yaml_string) {
    int quantity = atoi(parse_yaml(yaml_string, "quantity"));
    int price = get_product_price(parse_yaml(yaml_string, "product_code"));
    return itoa(quantity * price);
}