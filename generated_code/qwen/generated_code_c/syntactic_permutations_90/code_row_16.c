#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libyaml/yaml.h>

double get_price_for_product_code(const char* product_code) {
    if (strcmp(product_code, "A1") == 0) return 10.5;
    if (strcmp(product_code, "B2") == 0) return 20.3;
    if (strcmp(product_code, "C3") == 0) return 30.7;
    return 0.0; // Default price for unknown product codes
}

char* calculate_price(const char* yaml_payload) {
    yaml_parser_t parser;
    yaml_event_t event;
    int done = 0;
    const char* product_code = NULL;
    int quantity = 0;

    yaml_parser_initialize(&parser);
    yaml_parser_set_input_string(&parser, (unsigned char*)yaml_payload, strlen(yaml_payload));

    while (!done) {
        if (!yaml_parser_parse(&parser, &event)) {
            fprintf(stderr, "Parser error %d\n", parser.error);
            exit(EXIT_FAILURE);
        }

        switch (event.type) {
            case YAML_DOCUMENT_START_EVENT:
                break;
            case YAML_SCALAR_EVENT:
                if (product_code == NULL && strcmp((char*)event.data.scalar.value, "product_code") == 0) {
                    yaml_parser_parse(&parser, &event);
                    product_code = (char*)event.data.scalar.value;
                } else if (quantity == 0 && strcmp((char*)event.data.scalar.value, "quantity") == 0) {
                    yaml_parser_parse(&parser, &event);
                    quantity = atoi((char*)event.data.scalar.value);
                }
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

    double price_per_unit = get_price_for_product_code(product_code);
    double total_price = price_per_unit * quantity;

    char* result = malloc(100); // Allocate enough space for the YAML output
    snprintf(result, 100, "total_price: %.2f\n", total_price);

    return result;
}

int main() {
    const char* yaml_input = "product_code: A1\nquantity: 3";
    char* yaml_output = calculate_price(yaml_input);
    printf("%s", yaml_output);
    free(yaml_output); // Free the allocated memory for the YAML output
    return 0;
}