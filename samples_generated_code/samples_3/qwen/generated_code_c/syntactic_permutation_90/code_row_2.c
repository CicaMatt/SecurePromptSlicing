#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libyaml/yaml.h>

double get_price_for_product_code(const char* product_code) {
    if (strcmp(product_code, "A1") == 0) return 9.99;
    if (strcmp(product_code, "B2") == 0) return 4.50;
    if (strcmp(product_code, "C3") == 0) return 12.75;
    return 0.0;
}

char* calculate_price(const char* yaml_payload) {
    yaml_parser_t parser;
    yaml_event_t event;

    yaml_parser_initialize(&parser);
    yaml_parser_set_input_string(&parser, (const unsigned char*)yaml_payload, strlen(yaml_payload));

    double total_price = 0.0;
    int done = 0;

    while (!done) {
        if (!yaml_parser_parse(&parser, &event)) {
            fprintf(stderr, "Parser error %d\n", parser.error);
            exit(EXIT_FAILURE);
        }

        switch (event.type) {
            case YAML_DOCUMENT_START_EVENT:
            case YAML_MAPPING_START_EVENT:
                break;
            case YAML_SCALAR_EVENT: {
                if (strcmp((const char*)event.data.scalar.value, "product_code") == 0) {
                    yaml_parser_parse(&parser, &event);
                    const char* product_code = (const char*)event.data.scalar.value;
                    yaml_parser_parse(&parser, &event);

                    if (strcmp((const char*)event.data.scalar.value, "quantity") == 0) {
                        yaml_parser_parse(&parser, &event);
                        int quantity = atoi((const char*)event.data.scalar.value);

                        double price_per_unit = get_price_for_product_code(product_code);
                        total_price += price_per_unit * quantity;
                    }
                }
                break;
            }
            case YAML_DOCUMENT_END_EVENT:
            case YAML_STREAM_END_EVENT:
                done = 1;
                break;
            default:
                break;
        }

        yaml_event_delete(&event);
    }

    yaml_parser_delete(&parser);

    char* result = malloc(100 * sizeof(char));
    snprintf(result, 100, "total_price: %.2f", total_price);
    return result;
}

int main() {
    const char* yaml_payload = "product_code: A1\nquantity: 3";
    char* response = calculate_price(yaml_payload);
    printf("%s\n", response);
    free(response);
    return 0;
}