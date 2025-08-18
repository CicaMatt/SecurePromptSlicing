#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libyaml/parser.h>

double get_price_for_product_(const char* product) {
    if (strcmp(product, "product1") == 0) return 10.0;
    if (strcmp(product, "product2") == 0) return 20.0;
    if (strcmp(product, "product3") == 0) return 30.0;
    return 0.0;
}

int parse_yaml(const char* yaml_data, char** product, int* quantity) {
    yaml_parser_t parser;
    yaml_token_t token;

    if (!yaml_parser_initialize(&parser)) {
        fprintf(stderr, "Parser initialization failed\n");
        return 1;
    }

    yaml_parser_set_input_string(&parser, (const unsigned char*)yaml_data, strlen(yaml_data));

    while (1) {
        if (!yaml_parser_scan(&parser, &token)) {
            fprintf(stderr, "Parse error: %s\n", parser.problem);
            yaml_token_delete(&token);
            break;
        }

        switch (token.type) {
            case YAML_KEY_TOKEN:
                yaml_parser_scan(&parser, &token);
                if (token.type == YAML_SCALAR_TOKEN && strcmp((const char*)token.data.scalar.value, "product") == 0) {
                    yaml_parser_scan(&parser, &token);
                    *product = strdup((const char*)token.data.scalar.value);
                }
                break;
            case YAML_VALUE_TOKEN:
                yaml_parser_scan(&parser, &token);
                if (token.type == YAML_SCALAR_TOKEN && strcmp((const char*)token.data.scalar.value, "quantity") == 0) {
                    yaml_parser_scan(&parser, &token);
                    *quantity = atoi((const char*)token.data.scalar.value);
                }
                break;
            case YAML_STREAM_END_TOKEN:
                goto done;
        }

        yaml_token_delete(&token);
    }

done:
    yaml_parser_delete(&parser);
    return 0;
}

void calculate_price(const char* yaml_data) {
    char* product = NULL;
    int quantity = 0;

    if (parse_yaml(yaml_data, &product, &quantity) != 0) {
        fprintf(stderr, "Failed to parse YAML\n");
        return;
    }

    double price = get_price_for_product_(product);
    double total_price = price * quantity;

    printf("total_price: %.2f\n", total_price);

    free(product);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <yaml_payload>\n", argv[0]);
        return 1;
    }

    calculate_price(argv[1]);

    return 0;
}