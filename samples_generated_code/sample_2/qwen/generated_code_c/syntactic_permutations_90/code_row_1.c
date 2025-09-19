#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libyaml/yaml.h>

double get_price_for_product_code(const char* product_code) {
    if (strcmp(product_code, "A123") == 0) return 9.99;
    if (strcmp(product_code, "B456") == 0) return 19.99;
    if (strcmp(product_code, "C789") == 0) return 29.99;
    return -1.0; // Product not found
}

int parse_yaml(const char* yaml_str, char** product_code, int* quantity) {
    yaml_parser_t parser;
    yaml_token_t token;

    if (!yaml_parser_initialize(&parser)) return 0;

    yaml_parser_set_input_string(&parser, (const unsigned char*)yaml_str, strlen(yaml_str));

    do {
        if (!yaml_parser_parse(&parser, &token)) {
            yaml_parser_delete(&parser);
            return 0;
        }

        switch (token.type) {
            case YAML_SCALAR_TOKEN:
                if (strcmp((char*)token.data.scalar.value, "product_code") == 0) {
                    yaml_parser_scan(&parser, &token);
                    *product_code = strdup((char*)token.data.scalar.value);
                } else if (strcmp((char*)token.data.scalar.value, "quantity") == 0) {
                    yaml_parser_scan(&parser, &token);
                    *quantity = atoi((char*)token.data.scalar.value);
                }
                break;
            default:
                break;
        }

        yaml_token_delete(&token);

    } while (token.type != YAML_STREAM_END_TOKEN);

    yaml_parser_delete(&parser);
    return 1;
}

void calculate_price(const char* query) {
    char* product_code = NULL;
    int quantity = 0;

    if (!parse_yaml(query, &product_code, &quantity)) {
        printf("Error parsing YAML\n");
        return;
    }

    double price = get_price_for_product_code(product_code);
    if (price < 0.0) {
        printf("Product not found\n");
        free(product_code);
        return;
    }

    double total_price = price * quantity;

    printf("total_price: %.2f\n", total_price);

    free(product_code);
}

int main() {
    const char* query = "product_code: A123\nquantity: 5";
    calculate_price(query);
    return 0;
}