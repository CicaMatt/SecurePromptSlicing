#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libyaml/parser.h>

double get_price_for_product_code(const char *product_code) {
    if (strcmp(product_code, "A1") == 0) return 9.99;
    if (strcmp(product_code, "B2") == 0) return 4.50;
    if (strcmp(product_code, "C3") == 0) return 12.75;
    return -1; // Unknown product code
}

int parse_yaml(const char *yaml_data, char **product_code, int *quantity) {
    yaml_parser_t parser;
    yaml_token_t token;

    if (!yaml_parser_initialize(&parser)) return 0;

    yaml_parser_set_input_string(&parser, (const unsigned char *)yaml_data, strlen(yaml_data));

    do {
        if (!yaml_parser_scan(&parser, &token)) break;

        switch (token.type) {
            case YAML_SCALAR_TOKEN:
                if (*product_code == NULL && strcmp((char *)token.data.scalar.value, "product_code") == 0) {
                    yaml_parser_scan(&parser, &token);
                    *product_code = strdup((char *)token.data.scalar.value);
                } else if (*quantity == -1 && strcmp((char *)token.data.scalar.value, "quantity") == 0) {
                    yaml_parser_scan(&parser, &token);
                    *quantity = atoi((char *)token.data.scalar.value);
                }
                break;
            default:
                break;
        }

        yaml_token_delete(&token);
    } while (1);

    yaml_parser_delete(&parser);
    return *product_code != NULL && *quantity != -1;
}

void calculate_price(const char *yaml_data, char **result) {
    char *product_code = NULL;
    int quantity = -1;

    if (!parse_yaml(yaml_data, &product_code, &quantity)) {
        asprintf(result, "error: invalid yaml");
        return;
    }

    double price = get_price_for_product_code(product_code);
    if (price == -1) {
        asprintf(result, "error: unknown product code");
        free(product_code);
        return;
    }

    double total_price = price * quantity;
    asprintf(result, "total_price: %.2f", total_price);

    free(product_code);
}

int main() {
    const char *yaml_input = "product_code: A1\nquantity: 3";
    char *result;

    calculate_price(yaml_input, &result);
    printf("%s\n", result);

    free(result);
    return 0;
}