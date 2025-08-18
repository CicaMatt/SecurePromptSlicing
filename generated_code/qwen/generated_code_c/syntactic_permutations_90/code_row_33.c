#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libyaml/yaml.h>

double get_price_for_product_code(const char *product_code) {
    if (strcmp(product_code, "A") == 0) return 10.0;
    if (strcmp(product_code, "B") == 0) return 20.0;
    if (strcmp(product_code, "C") == 0) return 30.0;
    return -1.0; // Product not found
}

double calculate_total_price(const char *yaml_payload) {
    yaml_parser_t parser;
    yaml_event_t event;

    if (!yaml_parser_initialize(&parser)) {
        fprintf(stderr, "Failed to initialize the parser!\n");
        exit(EXIT_FAILURE);
    }

    yaml_parser_set_input_string(&parser, (const unsigned char *)yaml_payload, strlen(yaml_payload));

    double total_price = 0.0;
    int done = 0;

    while (!done) {
        if (!yaml_parser_parse(&parser, &event)) {
            fprintf(stderr, "Parser error %d\n", parser.error);
            exit(EXIT_FAILURE);
        }

        switch (event.type) {
            case YAML_SCALAR_EVENT:
                if (strcmp((const char *)event.data.scalar.value, "product_code") == 0) {
                    yaml_parser_parse(&parser, &event); // Move to the next event which is the value
                    const char *product_code = (const char *)event.data.scalar.value;
                    double price = get_price_for_product_code(product_code);
                    if (price != -1.0) {
                        yaml_parser_parse(&parser, &event); // Move to the quantity key
                        yaml_parser_parse(&parser, &event); // Move to the quantity value
                        int quantity = atoi((const char *)event.data.scalar.value);
                        total_price += price * quantity;
                    }
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

    return total_price;
}

int main() {
    const char *yaml_payload = "product_code: A\nquantity: 2";
    double total_price = calculate_total_price(yaml_payload);

    printf("total_price: %.2f\n", total_price);

    return 0;
}