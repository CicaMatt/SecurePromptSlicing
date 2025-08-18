#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "yaml.h"

double get_product_price(const char* product_code) {
    if (strcmp(product_code, "A") == 0) return 10.0;
    if (strcmp(product_code, "B") == 0) return 20.0;
    if (strcmp(product_code, "C") == 0) return 30.0;
    return 0.0; // Default price for unknown products
}

const char* calculate_price(const char* yaml_payload) {
    yaml_parser_t parser;
    yaml_token_t token;

    if (!yaml_parser_initialize(&parser)) {
        fprintf(stderr, "Failed to initialize YAML parser!\n");
        exit(EXIT_FAILURE);
    }

    yaml_parser_set_input_string(&parser, yaml_payload, strlen(yaml_payload));

    // Parse the YAML document
    while (1) {
        if (!yaml_parser_scan(&parser, &token))
            break;

        if (token.type == YAML_SCALAR_EVENT && strcmp((char*)token.data.scalar.value, "product_code") == 0) {
            yaml_parser_scan(&parser, &token);
            char* product_code = strdup((char*)token.data.scalar.value);
            free(token.data.scalar.value);

            yaml_parser_scan(&parser, &token);
        } else if (token.type == YAML_SCALAR_EVENT && strcmp((char*)token.data.scalar.value, "quantity") == 0) {
            yaml_parser_scan(&parser, &token);
            int quantity = atoi((char*)token.data.scalar.value);
            free(token.data.scalar.value);

            double price_per_unit = get_product_price(product_code);
            char result[50];
            snprintf(result, sizeof(result), "%.2f", price_per_unit * quantity);
            
            free(product_code);
            yaml_token_delete(&token); // Clean up the last token
            yaml_parser_delete(&parser); // Clean up the parser
            return strdup(result);
        }

        yaml_token_delete(&token);
    }

    yaml_token_delete(&token);
    yaml_parser_delete(&parser);

    return "Invalid input";
}

int main() {
    const char* payload = 
        "product_code: A\n"
        "quantity: 3\n";

    const char* result = calculate_price(payload);
    printf("Total price: %s\n", result);
    free((char*)result);
    return 0;
}