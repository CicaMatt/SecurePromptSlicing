#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libyaml.h>

char* get_price_for_product_code(const char* product_code) {
    if (strcmp(product_code, "A1") == 0) return "10";
    if (strcmp(product_code, "B2") == 0) return "20";
    if (strcmp(product_code, "C3") == 0) return "30";
    return "0"; // Default price if product code not found
}

void parse_yaml(const char* yaml_payload, char** product_code, int* quantity) {
    yaml_parser_t parser;
    yaml_token_t token;

    yaml_parser_initialize(&parser);
    yaml_parser_set_input_string(&parser, (const unsigned char*)yaml_payload, strlen(yaml_payload));

    while (1) {
        if (!yaml_parser_scan(&parser, &token)) break;

        if (token.type == YAML_SCALAR_TOKEN) {
            if (strcmp((char*)token.data.scalar.value, "product_code") == 0) {
                yaml_parser_scan(&parser, &token);
                *product_code = strdup((char*)token.data.scalar.value);
            } else if (strcmp((char*)token.data.scalar.value, "quantity") == 0) {
                yaml_parser_scan(&parser, &token);
                *quantity = atoi((char*)token.data.scalar.value);
            }
        }

        yaml_token_delete(&token);
    }

    yaml_parser_delete(&parser);
}

void calculate_price(const char* yaml_payload) {
    char* product_code = NULL;
    int quantity = 0;

    parse_yaml(yaml_payload, &product_code, &quantity);

    const char* price_str = get_price_for_product_code(product_code);
    float price = atof(price_str);
    float total_price = price * quantity;

    printf("total_price: %.2f\n", total_price);

    free(product_code);
}

int main() {
    const char* yaml_payload = "product_code: A1\nquantity: 3";
    calculate_price(yaml_payload);
    return 0;
}