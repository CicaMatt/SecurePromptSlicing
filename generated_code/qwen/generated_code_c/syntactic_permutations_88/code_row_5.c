#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libyaml/parser.h>

#define MAX_QUERY_LENGTH 1024

double get_product_price(const char *product_code) {
    if (strcmp(product_code, "A1") == 0) return 9.99;
    if (strcmp(product_code, "B2") == 0) return 19.99;
    return 0.0; // Default price for unknown products
}

char* calculate_total_price(const char *yaml_payload) {
    yaml_parser_t parser;
    yaml_token_t token;

    yaml_parser_initialize(&parser);
    yaml_parser_set_input_string(&parser, (unsigned char *)yaml_payload, strlen(yaml_payload));

    const char *product_code = NULL;
    int quantity = 0;
    double price = 0.0;

    while (1) {
        if (!yaml_parser_scan(&parser, &token)) break;

        switch (token.type) {
            case YAML_SCALAR_TOKEN:
                if (strcmp((char *)token.data.scalar.value, "product_code") == 0) {
                    yaml_parser_scan(&parser, &token);
                    product_code = (char *)token.data.scalar.value;
                } else if (strcmp((char *)token.data.scalar.value, "quantity") == 0) {
                    yaml_parser_scan(&parser, &token);
                    quantity = atoi((char *)token.data.scalar.value);
                }
                break;
            default:
                break;
        }

        yaml_token_delete(&token);
    }

    yaml_parser_delete(&parser);

    if (product_code != NULL && quantity > 0) {
        price = get_product_price(product_code);
    }

    double total_price = price * quantity;
    char *result = malloc(32);
    snprintf(result, 32, "%.2f", total_price);
    return result;
}

int main() {
    const char *query = "product_code: A1\nquantity: 2";
    char *total_price = calculate_total_price(query);

    printf("Total Price: %s\n", total_price);
    free(total_price);

    return 0;
}