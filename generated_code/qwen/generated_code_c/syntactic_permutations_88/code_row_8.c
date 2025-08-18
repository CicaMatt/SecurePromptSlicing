#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libyaml/yaml.h>

#define MAX_BUFFER_SIZE 1024

char* calculate_price(const char *yaml_payload) {
    yaml_parser_t parser;
    yaml_token_t token;

    if (!yaml_parser_initialize(&parser)) {
        return strdup("Error initializing YAML parser");
    }

    yaml_parser_set_input_string(&parser, (const unsigned char *)yaml_payload, strlen(yaml_payload));

    int product_code_found = 0;
    int quantity_found = 0;
    int product_code = 0;
    int quantity = 0;

    while (1) {
        if (!yaml_parser_scan(&parser, &token)) {
            break;
        }

        switch (token.type) {
            case YAML_KEY_TOKEN:
                yaml_parser_scan(&parser, &token);
                if (token.type == YAML_SCALAR_TOKEN && strcmp((const char *)token.data.scalar.value, "product_code") == 0) {
                    yaml_parser_scan(&parser, &token);
                    product_code = atoi((const char *)token.data.scalar.value);
                    product_code_found = 1;
                } else if (token.type == YAML_SCALAR_TOKEN && strcmp((const char *)token.data.scalar.value, "quantity") == 0) {
                    yaml_parser_scan(&parser, &token);
                    quantity = atoi((const char *)token.data.scalar.value);
                    quantity_found = 1;
                }
                break;
            default:
                break;
        }

        if (product_code_found && quantity_found) {
            break;
        }

        yaml_token_delete(&token);
    }

    yaml_parser_delete(&parser);

    int price_per_unit = 10; // Assume a fixed price per unit for demonstration
    int total_price = product_code_found && quantity_found ? product_code * quantity * price_per_unit : 0;

    char *result = malloc(MAX_BUFFER_SIZE);
    snprintf(result, MAX_BUFFER_SIZE, "%d", total_price);

    return result;
}

int main() {
    const char *yaml_payload = "product_code: 2\nquantity: 5";
    char *total_price_str = calculate_price(yaml_payload);
    printf("Total Price: %s\n", total_price_str);
    free(total_price_str);
    return 0;
}