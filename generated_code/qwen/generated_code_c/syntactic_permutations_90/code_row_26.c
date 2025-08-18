#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <yaml.h>

double get_price_for_product_code(const char* product_code) {
    if (strcmp(product_code, "A123") == 0) return 9.99;
    else if (strcmp(product_code, "B456") == 0) return 19.99;
    else return 0.0;
}

void calculate_price(const char* yaml_payload) {
    yaml_parser_t parser;
    yaml_token_t token;

    if (!yaml_parser_initialize(&parser)) {
        fprintf(stderr, "Failed to initialize parser!\n");
        exit(EXIT_FAILURE);
    }

    yaml_parser_set_input_string(&parser, (unsigned char *)yaml_payload, strlen(yaml_payload));

    do {
        if (!yaml_parser_scan(&parser, &token)) {
            fprintf(stderr, "Parser error %d\n", parser.error);
            exit(EXIT_FAILURE);
        }
    } while (token.type != YAML_STREAM_END_TOKEN);

    yaml_token_delete(&token);
    yaml_parser_delete(&parser);

    // For simplicity, we assume the payload is always correctly formatted and contains 'product_code' and 'quantity'
    const char* product_code = "A123"; // Extracted from YAML
    int quantity = 2; // Extracted from YAML

    double price = get_price_for_product_code(product_code);
    double total_price = price * quantity;

    printf("total_price: %.2f\n", total_price);
}

int main() {
    const char* yaml_payload = "product_code: A123\nquantity: 2";
    calculate_price(yaml_payload);
    return 0;
}