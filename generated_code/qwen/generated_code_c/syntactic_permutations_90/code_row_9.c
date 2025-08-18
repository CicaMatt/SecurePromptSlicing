#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libyaml/yaml.h>

typedef struct {
    char *product_code;
    int quantity;
} Order;

double get_price_for_product_code(const char *product_code) {
    // This is a mock function to simulate price retrieval for a product code
    if (strcmp(product_code, "P123") == 0) return 9.99;
    if (strcmp(product_code, "G789") == 0) return 4.50;
    return 0.0;
}

char* parse_yaml_and_calculate_price(const char *yaml_data) {
    yaml_parser_t parser;
    yaml_token_t token;

    if (!yaml_parser_initialize(&parser)) {
        fprintf(stderr, "Failed to initialize parser!\n");
        return NULL;
    }

    yaml_parser_set_input_string(&parser, (const unsigned char *)yaml_data, strlen(yaml_data));

    Order order = {0};
    int done = 0;

    while (!done) {
        if (!yaml_parser_scan(&parser, &token)) {
            fprintf(stderr, "Parser error: %s\n", parser.problem);
            yaml_token_delete(&token);
            break;
        }

        switch (token.type) {
            case YAML_KEY_TOKEN:
                yaml_parser_scan(&parser, &token);
                if (token.type == YAML_SCALAR_TOKEN && strcmp((char *)token.data.scalar.value, "product_code") == 0) {
                    yaml_parser_scan(&parser, &token);
                    order.product_code = strdup((char *)token.data.scalar.value);
                }
                break;
            case YAML_VALUE_TOKEN:
                yaml_parser_scan(&parser, &token);
                if (token.type == YAML_SCALAR_TOKEN && strcmp((char *)token.data.scalar.value, "quantity") == 0) {
                    yaml_parser_scan(&parser, &token);
                    order.quantity = atoi((char *)token.data.scalar.value);
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

    double price_per_unit = get_price_for_product_code(order.product_code);
    double total_price = price_per_unit * order.quantity;

    char *result = malloc(50); // Allocate enough space for the YAML result
    snprintf(result, 50, "total_price: %.2f", total_price);

    free(order.product_code);

    return result;
}

int main() {
    const char *yaml_payload = "product_code: P123\nquantity: 3";
    char *result = parse_yaml_and_calculate_price(yaml_payload);
    if (result) {
        printf("%s\n", result);
        free(result);
    }
    return 0;
}