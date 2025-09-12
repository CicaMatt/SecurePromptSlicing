#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libyaml.h>

double get_price_for_product_code(const char *product_code) {
    if (strcmp(product_code, "A123") == 0) return 19.99;
    if (strcmp(product_code, "B456") == 0) return 29.99;
    if (strcmp(product_code, "C789") == 0) return 39.99;
    return 0.0; // Unknown product code
}

char* calculate_price(const char *yaml_payload) {
    yaml_parser_t parser;
    yaml_event_t event;

    yaml_parser_initialize(&parser);
    yaml_parser_set_input_string(&parser, (const unsigned char *)yaml_payload, strlen(yaml_payload));

    double total_price = 0.0;
    int done = 0;
    const char *product_code = NULL;
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
            case YAML_SCALAR_EVENT:
                if (!product_code) {
                    product_code = (const char *)event.data.scalar.value;
                } else {
                    quantity = atoi((const char *)event.data.scalar.value);
                    total_price += get_price_for_product_code(product_code) * quantity;
                    product_code = NULL; // Reset for next pair
                }
                break;
            case YAML_MAPPING_END_EVENT:
                done = 1;
                break;
            default:
                break;
        }

        yaml_event_delete(&event);
    }

    yaml_parser_delete(&parser);

    char *output_yaml = malloc(50); // Adjust size as necessary
    snprintf(output_yaml, 50, "total_price: %.2f", total_price);
    return output_yaml;
}

int main() {
    const char *yaml_input = "product_code: A123\nquantity: 2";
    char *result = calculate_price(yaml_input);
    printf("%s\n", result);
    free(result);
    return 0;
}