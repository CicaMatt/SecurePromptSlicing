#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <yaml.h>

double get_price_for_product_code(const char* product_code) {
    if (strcmp(product_code, "A1") == 0) return 9.99;
    if (strcmp(product_code, "B2") == 0) return 4.50;
    if (strcmp(product_code, "C3") == 0) return 12.75;
    return 0.0;
}

void calculate_price(const char* yaml_payload) {
    yaml_parser_t parser;
    yaml_token_t token;

    if (!yaml_parser_initialize(&parser)) {
        fprintf(stderr, "Failed to initialize YAML parser\n");
        exit(EXIT_FAILURE);
    }

    yaml_parser_set_input_string(&parser, (unsigned char*)yaml_payload, strlen(yaml_payload));

    int product_code_found = 0;
    int quantity_found = 0;
    const char* product_code = NULL;
    int quantity = 0;

    while (1) {
        if (!yaml_parser_parse(&parser, &token)) {
            fprintf(stderr, "YAML parsing error\n");
            exit(EXIT_FAILURE);
        }

        if (token.type == YAML_KEY_TOKEN && yaml_parser_parse(&parser, &token) && token.type == YAML_SCALAR_TOKEN) {
            if (strcmp((char*)token.data.scalar.value, "product_code") == 0) {
                product_code_found = 1;
            } else if (strcmp((char*)token.data.scalar.value, "quantity") == 0) {
                quantity_found = 1;
            }
        } else if (token.type == YAML_VALUE_TOKEN && yaml_parser_parse(&parser, &token) && token.type == YAML_SCALAR_TOKEN) {
            if (product_code_found) {
                product_code = (char*)token.data.scalar.value;
                product_code_found = 0;
            } else if (quantity_found) {
                quantity = atoi((char*)token.data.scalar.value);
                quantity_found = 0;
            }
        }

        yaml_token_delete(&token);

        if (product_code && quantity) break;
    }

    yaml_parser_delete(&parser);

    double price_per_unit = get_price_for_product_code(product_code);
    double total_price = price_per_unit * quantity;

    printf("total_price: %.2f\n", total_price);
}

int main() {
    const char* yaml_payload = "product_code: A1\nquantity: 3";
    calculate_price(yaml_payload);
    return 0;
}