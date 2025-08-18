#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libyaml/yaml.h>

double get_price_for_product_code(const char* product_code) {
    if (strcmp(product_code, "A123") == 0) return 19.99;
    else if (strcmp(product_code, "B456") == 0) return 29.99;
    else if (strcmp(product_code, "C789") == 0) return 9.99;
    return 0.0;
}

void calculate_price(const char* yaml_input) {
    yaml_parser_t parser;
    yaml_token_t token;

    if (!yaml_parser_initialize(&parser)) {
        fprintf(stderr, "Failed to initialize parser!\n");
        exit(EXIT_FAILURE);
    }

    yaml_parser_set_input_string(&parser, (const unsigned char*)yaml_input, strlen(yaml_input));

    int done = 0;
    const char* product_code = NULL;
    int quantity = 0;

    while (!done) {
        if (!yaml_parser_parse(&parser, &token)) {
            fprintf(stderr, "Parser error %d\n", parser.error);
            yaml_token_delete(&token);
            yaml_parser_delete(&parser);
            exit(EXIT_FAILURE);
        }

        switch (token.type) {
            case YAML_KEY_TOKEN:
                yaml_parser_parse(&parser, &token);
                if (token.type == YAML_SCALAR_TOKEN && strcmp((const char*)token.data.scalar.value, "product_code") == 0) {
                    yaml_parser_parse(&parser, &token);
                    product_code = (const char*)token.data.scalar.value;
                }
                break;
            case YAML_VALUE_TOKEN:
                yaml_parser_parse(&parser, &token);
                if (token.type == YAML_SCALAR_TOKEN && strcmp((const char*)token.data.scalar.value, "quantity") == 0) {
                    yaml_parser_parse(&parser, &token);
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

    printf("total_price: %.2f\n", total_price);
}

int main() {
    const char* yaml_input = "product_code: A123\nquantity: 3";
    calculate_price(yaml_input);
    return 0;
}