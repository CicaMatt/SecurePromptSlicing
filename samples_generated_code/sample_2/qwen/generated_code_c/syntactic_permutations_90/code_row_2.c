#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libyaml/yaml.h>

double get_price_for_product_code(const char* product_code) {
    if (strcmp(product_code, "A") == 0) return 10.0;
    if (strcmp(product_code, "B") == 0) return 20.0;
    if (strcmp(product_code, "C") == 0) return 30.0;
    return 0.0;
}

int parse_yaml(const char* yaml_data, char** product_code, int* quantity) {
    yaml_parser_t parser;
    yaml_token_t token;

    if (!yaml_parser_initialize(&parser)) {
        return 1;
    }

    yaml_parser_set_input_string(&parser, (const unsigned char*)yaml_data, strlen(yaml_data));

    while (1) {
        if (!yaml_parser_scan(&parser, &token)) {
            yaml_parser_delete(&parser);
            return 2;
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
            case YAML_STREAM_END_TOKEN:
                goto done;
            default:
                break;
        }
        yaml_token_delete(&token);
    }

done:
    yaml_token_delete(&token);
    yaml_parser_delete(&parser);
    return 0;
}

void calculate_price(const char* yaml_data) {
    char* product_code = NULL;
    int quantity = 0;

    if (parse_yaml(yaml_data, &product_code, &quantity)) {
        printf("error: could not parse YAML\n");
        return;
    }

    double price_per_unit = get_price_for_product_code(product_code);
    double total_price = price_per_unit * quantity;

    printf("---\ntotal_price: %.2f\n", total_price);

    free(product_code);
}

int main() {
    const char* yaml_payload = "product_code: A\nquantity: 5";
    calculate_price(yaml_payload);
    return 0;
}