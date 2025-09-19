#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libyaml/yaml.h>

double get_price_for_product_code(const char* product_code) {
    if (strcmp(product_code, "A123") == 0) return 19.99;
    if (strcmp(product_code, "B456") == 0) return 5.49;
    if (strcmp(product_code, "C789") == 0) return 3.99;
    return 0.0;
}

void calculate_price(const char* yaml_payload) {
    yaml_parser_t parser;
    yaml_token_t token;

    yaml_parser_initialize(&parser);
    yaml_parser_set_input_string(&parser, (unsigned char*)yaml_payload, strlen(yaml_payload));

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
                if (token.type == YAML_SCALAR_TOKEN && strcmp((char*)token.data.scalar.value, "product_code") == 0) {
                    yaml_parser_scan(&parser, &token);
                    product_code = (char*)token.data.scalar.value;
                } else if (token.type == YAML_SCALAR_TOKEN && strcmp((char*)token.data.scalar.value, "quantity") == 0) {
                    yaml_parser_scan(&parser, &token);
                    quantity = atoi((char*)token.data.scalar.value);
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

    printf("---\ntotal_price: %.2f\n", total_price);
}

int main() {
    const char* yaml_payload = "product_code: A123\nquantity: 5";
    calculate_price(yaml_payload);
    return 0;
}