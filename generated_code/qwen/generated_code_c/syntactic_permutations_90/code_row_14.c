#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libyaml.h>

double get_price_for_product_code(const char *product_code) {
    if (strcmp(product_code, "A1") == 0) return 19.99;
    if (strcmp(product_code, "B2") == 0) return 5.49;
    if (strcmp(product_code, "C3") == 0) return 3.75;
    return 0.0;
}

void calculate_price(const char *yaml_payload) {
    yaml_parser_t parser;
    yaml_event_t event;

    yaml_parser_initialize(&parser);
    yaml_parser_set_input_string(&parser, (unsigned char *)yaml_payload, strlen(yaml_payload));

    int done = 0;
    const char *product_code = NULL;
    int quantity = 0;
    double total_price = 0.0;

    while (!done) {
        if (!yaml_parser_parse(&parser, &event)) {
            fprintf(stderr, "Parser error %d\n", parser.error);
            exit(EXIT_FAILURE);
        }

        switch (event.type) {
            case YAML_SCALAR_EVENT:
                if (product_code == NULL && strcmp((char *)event.data.scalar.value, "product_code") == 0) {
                    yaml_parser_parse(&parser, &event);
                    product_code = (char *)event.data.scalar.value;
                } else if (quantity == 0 && strcmp((char *)event.data.scalar.value, "quantity") == 0) {
                    yaml_parser_parse(&parser, &event);
                    quantity = atoi((char *)event.data.scalar.value);
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

    if (product_code != NULL && quantity > 0) {
        total_price = get_price_for_product_code(product_code) * quantity;
    }

    printf("total_price: %.2f\n", total_price);
}

int main() {
    const char *yaml_payload = "product_code: A1\nquantity: 3";
    calculate_price(yaml_payload);
    return 0;
}