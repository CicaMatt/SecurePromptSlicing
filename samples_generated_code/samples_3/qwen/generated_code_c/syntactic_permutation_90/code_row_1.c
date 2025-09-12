#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libyaml/parser.h>

double get_price_for_product_code(const char* product_code) {
    if (strcmp(product_code, "A123") == 0) return 9.99;
    if (strcmp(product_code, "B456") == 0) return 12.49;
    if (strcmp(product_code, "C789") == 0) return 15.99;
    return 0.0;
}

int parse_yaml(const char* yaml_data, char** product_code, int* quantity) {
    yaml_parser_t parser;
    yaml_token_t token;

    if (!yaml_parser_initialize(&parser)) {
        fprintf(stderr, "Failed to initialize the YAML parser\n");
        return -1;
    }

    yaml_parser_set_input_string(&parser, (const unsigned char*)yaml_data, strlen(yaml_data));

    while (1) {
        yaml_parser_scan(&parser, &token);

        switch (token.type) {
            case YAML_KEY_TOKEN:
                yaml_parser_scan(&parser, &token);
                if (strcmp((const char*)token.data.scalar.value, "product_code") == 0) {
                    yaml_parser_scan(&parser, &token);
                    *product_code = strdup((const char*)token.data.scalar.value);
                }
                break;
            case YAML_SCALAR_TOKEN:
                if (strcmp((const char*)token.data.scalar.value, "quantity") == 0) {
                    yaml_parser_scan(&parser, &token);
                    *quantity = atoi((const char*)token.data.scalar.value);
                }
                break;
            case YAML_STREAM_END_TOKEN:
                goto done;
            default:
                break;
        }

        yaml_token_delete(&token);
    }

done:
    yaml_token_delete(&token);
    yaml_parser_delete(&parser);

    return 0;
}

char* calculate_price(const char* yaml_data) {
    char* product_code = NULL;
    int quantity = 0;

    if (parse_yaml(yaml_data, &product_code, &quantity) != 0) {
        fprintf(stderr, "Failed to parse YAML data\n");
        return strdup("error: failed to parse YAML data");
    }

    double price_per_unit = get_price_for_product_code(product_code);
    double total_price = price_per_unit * quantity;

    char* result = malloc(256);
    snprintf(result, 256, "total_price: %.2f", total_price);

    free(product_code);

    return result;
}

int main() {
    const char* yaml_input = "product_code: A123\nquantity: 2";
    char* output = calculate_price(yaml_input);
    printf("%s\n", output);
    free(output);

    return 0;
}