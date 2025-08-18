#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libyaml.h>

#define MAX_BUFFER_SIZE 1024

const char* get_product_price(const char* product_code) {
    if (strcmp(product_code, "A1") == 0) return "10.99";
    if (strcmp(product_code, "B2") == 0) return "5.49";
    return "0.00"; // Default price for unknown products
}

char* calculate_price(const char* yaml_payload) {
    yaml_parser_t parser;
    yaml_token_t token;

    if (!yaml_parser_initialize(&parser)) {
        fprintf(stderr, "Parser initialization failed\n");
        exit(EXIT_FAILURE);
    }

    yaml_parser_set_input_string(&parser, (const unsigned char*)yaml_payload, strlen(yaml_payload));

    char product_code[10] = "";
    int quantity = 0;
    int found_product_code = 0;
    int found_quantity = 0;

    while (1) {
        if (!yaml_parser_parse(&parser, &token)) {
            fprintf(stderr, "Parser error %d\n", parser.problem);
            exit(EXIT_FAILURE);
        }

        switch (token.type) {
            case YAML_SCALAR_TOKEN:
                if (strcmp((const char*)token.data.scalar.value, "product_code") == 0) {
                    yaml_parser_parse(&parser, &token);
                    strncpy(product_code, (const char*)token.data.scalar.value, sizeof(product_code));
                    product_code[sizeof(product_code) - 1] = '\0';
                    found_product_code = 1;
                } else if (strcmp((const char*)token.data.scalar.value, "quantity") == 0) {
                    yaml_parser_parse(&parser, &token);
                    quantity = atoi((const char*)token.data.scalar.value);
                    found_quantity = 1;
                }
                break;
            case YAML_STREAM_END_TOKEN:
                goto end;
            default:
                break;
        }

        if (found_product_code && found_quantity) {
            break;
        }

        yaml_token_delete(&token);
    }

end:
    yaml_token_delete(&token);
    yaml_parser_delete(&parser);

    double price = atof(get_product_price(product_code));
    double total_price = price * quantity;

    char* result = malloc(MAX_BUFFER_SIZE);
    snprintf(result, MAX_BUFFER_SIZE, "%.2f", total_price);

    return result;
}

int main() {
    const char* yaml_payload = "product_code: A1\nquantity: 3";
    char* result = calculate_price(yaml_payload);
    printf("Total Price: %s\n", result);
    free(result);
    return 0;
}