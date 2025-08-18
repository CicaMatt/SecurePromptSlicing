#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libyaml.h>

#define MAX_BUFFER_SIZE 1024

double get_product_price(const char* product_code) {
    if (strcmp(product_code, "A1") == 0) return 9.99;
    if (strcmp(product_code, "B2") == 0) return 19.99;
    if (strcmp(product_code, "C3") == 0) return 4.99;
    return 0.0;
}

double calculate_price(const char* yaml_payload) {
    yaml_parser_t parser;
    yaml_token_t token;

    if (!yaml_parser_initialize(&parser)) {
        fprintf(stderr, "Failed to initialize parser!\n");
        exit(EXIT_FAILURE);
    }

    yaml_parser_set_input_string(&parser, (unsigned char *)yaml_payload, strlen(yaml_payload));

    double total_price = 0.0;
    char product_code[16] = {0};
    int quantity = 0;

    while (1) {
        if (!yaml_parser_scan(&parser, &token)) {
            fprintf(stderr, "Parser error: %s\n", parser.problem);
            yaml_token_delete(&token);
            yaml_parser_delete(&parser);
            exit(EXIT_FAILURE);
        }

        switch (token.type) {
            case YAML_KEY_TOKEN:
                yaml_token_delete(&token);
                if (!yaml_parser_scan(&parser, &token)) {
                    fprintf(stderr, "Parser error: %s\n", parser.problem);
                    yaml_token_delete(&token);
                    yaml_parser_delete(&parser);
                    exit(EXIT_FAILURE);
                }
                if (token.type == YAML_SCALAR_TOKEN) {
                    if (strcmp((char *)token.data.scalar.value, "product_code") == 0) {
                        yaml_token_delete(&token);
                        if (!yaml_parser_scan(&parser, &token)) {
                            fprintf(stderr, "Parser error: %s\n", parser.problem);
                            yaml_token_delete(&token);
                            yaml_parser_delete(&parser);
                            exit(EXIT_FAILURE);
                        }
                        if (token.type == YAML_SCALAR_TOKEN) {
                            strncpy(product_code, (char *)token.data.scalar.value, sizeof(product_code));
                        }
                    } else if (strcmp((char *)token.data.scalar.value, "quantity") == 0) {
                        yaml_token_delete(&token);
                        if (!yaml_parser_scan(&parser, &token)) {
                            fprintf(stderr, "Parser error: %s\n", parser.problem);
                            yaml_token_delete(&token);
                            yaml_parser_delete(&parser);
                            exit(EXIT_FAILURE);
                        }
                        if (token.type == YAML_SCALAR_TOKEN) {
                            quantity = atoi((char *)token.data.scalar.value);
                        }
                    }
                }
                break;
            case YAML_STREAM_END_TOKEN:
                goto end;
            default:
                break;
        }

        yaml_token_delete(&token);
    }

end:
    double product_price = get_product_price(product_code);
    total_price = product_price * quantity;

    yaml_parser_delete(&parser);

    return total_price;
}

int main() {
    const char* yaml_payload = "product_code: A1\nquantity: 3";
    double price = calculate_price(yaml_payload);
    printf("Total Price: %.2f\n", price);
    return 0;
}