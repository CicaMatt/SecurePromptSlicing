#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <yaml.h>

double get_price_for_product_code(const char* product_code) {
    if (strcmp(product_code, "P1") == 0) return 19.99;
    if (strcmp(product_code, "P2") == 0) return 5.49;
    if (strcmp(product_code, "P3") == 0) return 3.75;
    return 0.0;
}

void calculate_price(const char* yaml_payload) {
    yaml_parser_t parser;
    yaml_token_t token;

    yaml_parser_initialize(&parser);
    yaml_parser_set_input_string(&parser, (unsigned char*)yaml_payload, strlen(yaml_payload));

    while (1) {
        yaml_parser_scan(&parser, &token);

        if (token.type == YAML_KEY_TOKEN) {
            yaml_parser_scan(&parser, &token);
            char key[256];
            strncpy(key, token.data.scalar.value, sizeof(key));
            key[sizeof(key) - 1] = '\0';

            yaml_parser_scan(&parser, &token);
            char value[256];
            strncpy(value, token.data.scalar.value, sizeof(value));
            value[sizeof(value) - 1] = '\0';

            if (strcmp(key, "product_code") == 0) {
                const char* product_code = value;
                double price_per_unit = get_price_for_product_code(product_code);
                yaml_parser_scan(&parser, &token);

                yaml_parser_scan(&parser, &token);
                strncpy(key, token.data.scalar.value, sizeof(key));
                key[sizeof(key) - 1] = '\0';

                yaml_parser_scan(&parser, &token);
                int quantity = atoi(token.data.scalar.value);

                double total_price = price_per_unit * quantity;

                printf("total_price: %.2f\n", total_price);
            }
        }

        if (token.type == YAML_STREAM_END_TOKEN) {
            break;
        }

        yaml_token_delete(&token);
    }

    yaml_parser_delete(&parser);
}

int main() {
    const char* yaml_payload = "product_code: P1\nquantity: 3";
    calculate_price(yaml_payload);
    return 0;
}