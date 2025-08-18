#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libyaml.h>

const char* calculate_price(const char* yaml_payload) {
    yaml_parser_t parser;
    yaml_token_t token;

    const char* product_code = NULL;
    int quantity = 0;
    double price = 0.0;
    int done = 0;

    if (!yaml_parser_initialize(&parser)) {
        fprintf(stderr, "Failed to initialize parser!\n");
        return "";
    }

    yaml_parser_set_input_string(&parser, (unsigned char*)yaml_payload, strlen(yaml_payload));

    while (!done) {
        if (!yaml_parser_scan(&parser, &token)) {
            fprintf(stderr, "Parser error %d\n", parser.error);
            yaml_token_delete(&token);
            yaml_parser_delete(&parser);
            return "";
        }

        switch (token.type) {
            case YAML_KEY_TOKEN:
                yaml_token_delete(&token);
                if (!yaml_parser_scan(&parser, &token)) {
                    fprintf(stderr, "Parser error %d\n", parser.error);
                    yaml_token_delete(&token);
                    yaml_parser_delete(&parser);
                    return "";
                }
                if (token.type == YAML_SCALAR_TOKEN) {
                    if (strcmp((const char*)token.data.scalar.value, "product_code") == 0) {
                        yaml_token_delete(&token);
                        if (!yaml_parser_scan(&parser, &token)) {
                            fprintf(stderr, "Parser error %d\n", parser.error);
                            yaml_token_delete(&token);
                            yaml_parser_delete(&parser);
                            return "";
                        }
                        product_code = (const char*)token.data.scalar.value;
                    } else if (strcmp((const char*)token.data.scalar.value, "quantity") == 0) {
                        yaml_token_delete(&token);
                        if (!yaml_parser_scan(&parser, &token)) {
                            fprintf(stderr, "Parser error %d\n", parser.error);
                            yaml_token_delete(&token);
                            yaml_parser_delete(&parser);
                            return "";
                        }
                        quantity = atoi((const char*)token.data.scalar.value);
                    } else if (strcmp((const char*)token.data.scalar.value, "price") == 0) {
                        yaml_token_delete(&token);
                        if (!yaml_parser_scan(&parser, &token)) {
                            fprintf(stderr, "Parser error %d\n", parser.error);
                            yaml_token_delete(&token);
                            yaml_parser_delete(&parser);
                            return "";
                        }
                        price = atof((const char*)token.data.scalar.value);
                    }
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

    if (product_code && quantity > 0 && price > 0) {
        double total_price = price * quantity;
        char* result = malloc(50);
        snprintf(result, 50, "%.2f", total_price);
        return result;
    }

    return "Invalid input";
}

int main() {
    const char* yaml_payload = 
        "---\n"
        "product_code: ABC123\n"
        "quantity: 5\n"
        "price: 9.99\n"
        "...";

    const char* total_price = calculate_price(yaml_payload);
    printf("Total Price: %s\n", total_price);

    return 0;
}