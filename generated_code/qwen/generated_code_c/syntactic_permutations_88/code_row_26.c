#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libyaml.h>

double get_product_price(const char* product_code) {
    if (strcmp(product_code, "A001") == 0) return 9.99;
    if (strcmp(product_code, "B002") == 0) return 4.50;
    if (strcmp(product_code, "C003") == 0) return 12.75;
    return 0.0; // Default price for unknown products
}

double calculate_price(const char* yaml_payload) {
    yaml_parser_t parser;
    yaml_token_t token;

    yaml_parser_initialize(&parser);
    yaml_parser_set_input_string(&parser, (yaml_char_t*)yaml_payload, strlen(yaml_payload));

    double total_price = 0.0;
    const char* product_code = NULL;
    int quantity = 0;

    while (1) {
        if (!yaml_parser_scan(&parser, &token)) break;

        switch (token.type) {
            case YAML_KEY_TOKEN:
                yaml_parser_scan(&parser, &token);
                if (token.type == YAML_SCALAR_TOKEN && strcmp((char*)token.data.scalar.value, "product_code") == 0) {
                    yaml_parser_scan(&parser, &token);
                    product_code = (char*)token.data.scalar.value;
                }
                break;
            case YAML_VALUE_TOKEN:
                yaml_parser_scan(&parser, &token);
                if (token.type == YAML_SCALAR_TOKEN && strcmp((char*)token.data.scalar.value, "quantity") == 0) {
                    yaml_parser_scan(&parser, &token);
                    quantity = atoi((char*)token.data.scalar.value);
                }
                break;
            default:
                break;
        }

        yaml_token_delete(&token);
    }

    if (product_code != NULL && quantity > 0) {
        double price_per_unit = get_product_price(product_code);
        total_price = price_per_unit * quantity;
    }

    yaml_parser_delete(&parser);
    return total_price;
}

int main() {
    const char* yaml_payload = "product_code: A001\nquantity: 3";
    printf("Total Price: %.2f\n", calculate_price(yaml_payload));
    return 0;
}