#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libyaml.h>

double get_price_for_product_code(const char* product_code) {
    if (strcmp(product_code, "A001") == 0) return 9.99;
    if (strcmp(product_code, "B002") == 0) return 4.50;
    if (strcmp(product_code, "C003") == 0) return 12.75;
    return 0.0;
}

char* calculate_price(const char* yaml_payload) {
    yaml_parser_t parser;
    yaml_event_t event;

    yaml_parser_initialize(&parser);
    yaml_parser_set_input_string(&parser, (unsigned char*)yaml_payload, strlen(yaml_payload));

    int done = 0;
    char* product_code = NULL;
    int quantity = 0;

    while (!done) {
        if (!yaml_parser_parse(&parser, &event)) {
            fprintf(stderr, "Parser error %d\n", parser.error);
            exit(EXIT_FAILURE);
        }

        switch (event.type) {
            case YAML_SCALAR_EVENT:
                if (product_code == NULL && strcmp((char*)event.data.scalar.value, "product_code") == 0) {
                    yaml_parser_parse(&parser, &event);
                    product_code = strdup((char*)event.data.scalar.value);
                } else if (strcmp((char*)event.data.scalar.value, "quantity") == 0) {
                    yaml_parser_parse(&parser, &event);
                    quantity = atoi((char*)event.data.scalar.value);
                }
                break;
            case YAML_STREAM_END_EVENT:
                done = 1;
                break;
            default:
                break;
        }

        yaml_event_delete(&event);
    }

    yaml_parser_delete(&parser);

    double price = get_price_for_product_code(product_code) * quantity;

    char* response = malloc(50);
    sprintf(response, "total_price: %.2f", price);

    return response;
}

int main() {
    const char* yaml_input = "product_code: A001\nquantity: 3";
    char* result = calculate_price(yaml_input);
    printf("%s\n", result);
    free(result);
    return 0;
}