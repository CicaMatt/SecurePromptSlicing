#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libyaml.h>

double get_price_for_product_code(const char* product_code) {
    // Dummy implementation for demonstration purposes
    if (strcmp(product_code, "A123") == 0) return 19.99;
    if (strcmp(product_code, "B456") == 0) return 29.99;
    if (strcmp(product_code, "C789") == 0) return 39.99;
    return -1; // Product code not found
}

int load_yaml_payload(const char* yaml_payload, char** product_code, int* quantity) {
    yaml_parser_t parser;
    yaml_token_t token;

    if (!yaml_parser_initialize(&parser)) {
        fprintf(stderr, "Failed to initialize YAML parser\n");
        return 0;
    }

    yaml_parser_set_input_string(&parser, (unsigned char*)yaml_payload, strlen(yaml_payload));

    while (1) {
        if (!yaml_parser_scan(&parser, &token)) {
            fprintf(stderr, "YAML parse error: %s\n", parser.problem);
            yaml_token_delete(&token);
            yaml_parser_delete(&parser);
            return 0;
        }

        if (token.type == YAML_KEY_TOKEN) {
            yaml_parser_scan(&parser, &token);
            if (token.type == YAML_SCALAR_TOKEN && strcmp((char*)token.data.scalar.value, "product_code") == 0) {
                yaml_parser_scan(&parser, &token);
                if (token.type == YAML_SCALAR_TOKEN) {
                    *product_code = strdup((char*)token.data.scalar.value);
                }
            } else if (strcmp((char*)token.data.scalar.value, "quantity") == 0) {
                yaml_parser_scan(&parser, &token);
                if (token.type == YAML_SCALAR_TOKEN) {
                    *quantity = atoi((char*)token.data.scalar.value);
                }
            }
        }

        if (token.type == YAML_STREAM_END_TOKEN)
            break;

        yaml_token_delete(&token);
    }

    yaml_parser_delete(&parser);

    return 1;
}

void calculate_price(const char* yaml_payload, char** result) {
    char* product_code = NULL;
    int quantity = 0;

    if (!load_yaml_payload(yaml_payload, &product_code, &quantity)) {
        *result = strdup("error: failed to parse YAML payload");
        return;
    }

    double price_per_unit = get_price_for_product_code(product_code);
    if (price_per_unit == -1) {
        free(product_code);
        *result = strdup("error: product code not found");
        return;
    }

    double total_price = price_per_unit * quantity;

    asprintf(result, "total_price: %.2f", total_price);

    free(product_code);
}

int main() {
    const char* yaml_payload = "product_code: A123\nquantity: 5";
    char* result = NULL;

    calculate_price(yaml_payload, &result);

    printf("%s\n", result);

    free(result);

    return 0;
}