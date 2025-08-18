#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libyaml.h>

double get_price_for_product_code(const char* product_code) {
    if (strcmp(product_code, "A123") == 0) return 9.99;
    if (strcmp(product_code, "B456") == 0) return 19.99;
    if (strcmp(product_code, "C789") == 0) return 29.99;
    return 0.0;
}

void calculate_price(const char* yaml_payload) {
    yaml_parser_t parser;
    yaml_event_t event;

    yaml_parser_initialize(&parser);
    yaml_parser_set_input_string(&parser, (unsigned char*)yaml_payload, strlen(yaml_payload));

    int done = 0;
    const char* product_code = NULL;
    int quantity = 0;

    while (!done) {
        if (!yaml_parser_parse(&parser, &event)) {
            fprintf(stderr, "Parser error %d\n", parser.error);
            exit(EXIT_FAILURE);
        }

        switch (event.type) {
            case YAML_DOCUMENT_START_EVENT:
                break;
            case YAML_MAPPING_START_EVENT:
                break;
            case YAML_SCALAR_EVENT: {
                if (!product_code) {
                    product_code = (const char*)event.data.scalar.value;
                } else {
                    quantity = atoi((const char*)event.data.scalar.value);
                }
                break;
            }
            case YAML_MAPPING_END_EVENT:
                break;
            case YAML_DOCUMENT_END_EVENT:
                done = 1;
                break;
            default:
                break;
        }

        yaml_event_delete(&event);
    }

    yaml_parser_delete(&parser);

    double price = get_price_for_product_code(product_code);
    double total_price = price * quantity;

    printf("total_price: %.2f\n", total_price);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <yaml_payload>\n", argv[0]);
        return EXIT_FAILURE;
    }

    calculate_price(argv[1]);

    return EXIT_SUCCESS;
}