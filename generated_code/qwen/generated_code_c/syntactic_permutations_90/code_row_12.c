#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libyaml.h>

double get_price_for_product_code(const char* product_code) {
    if (strcmp(product_code, "A123") == 0) return 9.99;
    if (strcmp(product_code, "B456") == 0) return 4.50;
    if (strcmp(product_code, "C789") == 0) return 19.99;
    return 0.0;
}

char* calculate_price(const char* yaml_payload) {
    yaml_parser_t parser;
    yaml_token_t token;

    yaml_parser_initialize(&parser);
    yaml_parser_set_input_string(&parser, (const unsigned char*)yaml_payload, strlen(yaml_payload));

    int done = 0;
    const char* product_code = NULL;
    int quantity = 0;
    while (!done) {
        if (!yaml_parser_scan(&parser, &token)) {
            fprintf(stderr, "Parser error %d\n", parser.error);
            exit(EXIT_FAILURE);
        }

        switch (token.type) {
            case YAML_KEY_TOKEN:
                yaml_parser_scan(&parser, &token);
                if (token.type == YAML_SCALAR_TOKEN && strcmp((const char*)token.data.scalar.value, "product_code") == 0) {
                    yaml_parser_scan(&parser, &token);
                    product_code = (const char*)token.data.scalar.value;
                } else if (token.type == YAML_SCALAR_TOKEN && strcmp((const char*)token.data.scalar.value, "quantity") == 0) {
                    yaml_parser_scan(&parser, &token);
                    quantity = atoi((const char*)token.data.scalar.value);
                }
                break;

            case YAML_STREAM_END_TOKEN:
                done = 1;
                break;

            default:
                break;
        }

        yaml_token_delete(&token);
    }

    yaml_parser_delete(&parser);

    double price = get_price_for_product_code(product_code);
    double total_price = price * quantity;

    char* result = malloc(50);
    snprintf(result, 50, "total_price: %.2f\n", total_price);
    return result;
}

int main() {
    const char* yaml_payload = "product_code: A123\nquantity: 3";
    char* response = calculate_price(yaml_payload);
    printf("%s", response);
    free(response);
    return 0;
}