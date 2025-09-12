#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libyaml.h>

double get_price_for_product_code(const char* product_code) {
    if (strcmp(product_code, "A123") == 0) return 9.99;
    if (strcmp(product_code, "B456") == 0) return 4.99;
    if (strcmp(product_code, "C789") == 0) return 14.99;
    return 0.0; // Default price for unknown product codes
}

void calculate_price(const char* yaml_payload) {
    yaml_parser_t parser;
    yaml_event_t event;

    if (!yaml_parser_initialize(&parser)) {
        fprintf(stderr, "Failed to initialize parser!\n");
        exit(EXIT_FAILURE);
    }

    yaml_parser_set_input_string(&parser, (unsigned char*)yaml_payload, strlen(yaml_payload));

    int done = 0;
    const char* product_code = NULL;
    int quantity = 0;

    while (!done) {
        if (!yaml_parser_parse(&parser, &event)) {
            fprintf(stderr, "Parser error %d!\n", parser.error);
            exit(EXIT_FAILURE);
        }

        switch (event.type) {
            case YAML_DOCUMENT_START_EVENT:
                break;
            case YAML_MAPPING_START_EVENT:
                break;
            case YAML_SCALAR_EVENT: {
                if (!product_code && strcmp((char*)event.data.scalar.value, "product_code") == 0) {
                    yaml_parser_parse(&parser, &event);
                    product_code = (char*)event.data.scalar.value;
                } else if (!quantity && strcmp((char*)event.data.scalar.value, "quantity") == 0) {
                    yaml_parser_parse(&parser, &event);
                    quantity = atoi((char*)event.data.scalar.value);
                }
                break;
            }
            case YAML_MAPPING_END_EVENT:
                done = 1;
                break;
            case YAML_DOCUMENT_END_EVENT:
                break;
            default:
                break;
        }

        yaml_event_delete(&event);
    }

    yaml_parser_delete(&parser);

    double price_per_unit = get_price_for_product_code(product_code);
    double total_price = price_per_unit * quantity;

    printf("total_price: %.2f\n", total_price);
}

int main() {
    const char* yaml_input = "product_code: A123\nquantity: 5";
    calculate_price(yaml_input);
    return 0;
}