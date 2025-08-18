#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <yaml.h>

double get_product_price(const char* product_code) {
    if (strcmp(product_code, "A1") == 0) return 9.99;
    if (strcmp(product_code, "B2") == 0) return 4.50;
    if (strcmp(product_code, "C3") == 0) return 12.75;
    return 0.0; // Default price if product code is not found
}

double calculate_price(const char* yaml_payload) {
    yaml_parser_t parser;
    yaml_token_t token;
    int done = 0;

    const char* product_code = NULL;
    int quantity = 0;
    double total_price = 0.0;

    if (!yaml_parser_initialize(&parser)) {
        fprintf(stderr, "Failed to initialize YAML parser\n");
        return -1;
    }

    yaml_parser_set_input_string(&parser, (unsigned char*)yaml_payload, strlen(yaml_payload));

    while (!done) {
        if (!yaml_parser_parse(&parser, &token)) {
            fprintf(stderr, "Parser error %d\n", parser.error);
            yaml_token_delete(&token);
            yaml_parser_delete(&parser);
            return -1;
        }

        switch (token.type) {
            case YAML_KEY_TOKEN:
                yaml_parser_scan(&parser, &token);
                if (token.type == YAML_SCALAR_TOKEN && strcmp((char*)token.data.scalar.value, "product_code") == 0) {
                    yaml_parser_scan(&parser, &token);
                    product_code = (const char*)token.data.scalar.value;
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

    if (product_code && quantity > 0) {
        total_price = get_product_price(product_code) * quantity;
    }

    return total_price;
}

int main() {
    const char* yaml_payload = "product_code: A1\nquantity: 3";
    double price = calculate_price(yaml_payload);
    printf("Total Price: %.2f\n", price);
    return 0;
}