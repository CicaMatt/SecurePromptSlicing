#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libyaml.h>

double get_price_for_product_code(const char* product_code) {
    if (strcmp(product_code, "A123") == 0) return 9.99;
    if (strcmp(product_code, "B456") == 0) return 19.99;
    if (strcmp(product_code, "C789") == 0) return 29.99;
    return -1; // Unknown product code
}

double calculate_price(const char* yaml_payload) {
    yaml_parser_t parser;
    yaml_event_t event;

    double total_price = 0.0;
    const char* product_code = NULL;
    int quantity = 0;
    int done = 0;

    if (!yaml_parser_initialize(&parser)) {
        fprintf(stderr, "Failed to initialize the YAML parser\n");
        return -1;
    }

    yaml_parser_set_input_string(&parser, (const unsigned char*)yaml_payload, strlen(yaml_payload));

    while (!done) {
        if (!yaml_parser_parse(&parser, &event)) {
            fprintf(stderr, "Parser error %d: %s at line %ld, column %ld\n",
                    parser.error,
                    yaml_strerror(parser.error),
                    (long)parser.problem_mark.line + 1,
                    (long)parser.problem_mark.column + 1);
            break;
        }

        switch (event.type) {
            case YAML_DOCUMENT_START_EVENT:
                break;
            case YAML_MAPPING_START_EVENT:
                break;
            case YAML_SCALAR_EVENT:
                if (!product_code) {
                    product_code = (const char*)event.data.scalar.value;
                } else if (!quantity) {
                    quantity = atoi((const char*)event.data.scalar.value);
                }
                break;
            case YAML_MAPPING_END_EVENT:
                break;
            case YAML_DOCUMENT_END_EVENT:
                done = 1;
                break;
            default:
                fprintf(stderr, "Unexpected event type %d\n", event.type);
                done = 1;
                break;
        }

        yaml_event_delete(&event);

        if (product_code && quantity) {
            double price_per_unit = get_price_for_product_code(product_code);
            if (price_per_unit != -1) {
                total_price += price_per_unit * quantity;
            } else {
                fprintf(stderr, "Unknown product code: %s\n", product_code);
            }
            product_code = NULL;
            quantity = 0;
        }
    }

    yaml_parser_delete(&parser);

    return total_price;
}

int main() {
    const char* yaml_payload = "product_code: A123\nquantity: 2";
    double price = calculate_price(yaml_payload);
    if (price != -1) {
        printf("Total Price: %.2f\n", price);
    }
    return 0;
}