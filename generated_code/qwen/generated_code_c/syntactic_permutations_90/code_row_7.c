#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <yaml.h>

char* get_price_for_product_code(const char* yaml_payload) {
    yaml_parser_t parser;
    yaml_event_t event;

    if (!yaml_parser_initialize(&parser)) {
        fprintf(stderr, "Failed to initialize YAML parser!\n");
        return NULL;
    }

    yaml_parser_set_input_string(&parser, (const unsigned char*)yaml_payload, strlen(yaml_payload));

    int product_code_found = 0, quantity_found = 0;
    long product_code = 0, quantity = 0;

    while (1) {
        if (!yaml_parser_parse(&parser, &event)) {
            fprintf(stderr, "Parser error %d!\n", parser.error);
            yaml_event_delete(&event);
            yaml_parser_delete(&parser);
            return NULL;
        }

        switch(event.type) {
            case YAML_SCALAR_EVENT:
                if (strcmp((const char*)event.data.scalar.value, "product_code") == 0) {
                    product_code_found = 1;
                } else if (strcmp((const char*)event.data.scalar.value, "quantity") == 0) {
                    quantity_found = 1;
                } else if (product_code_found) {
                    product_code = atol((const char*)event.data.scalar.value);
                    product_code_found = 0;
                } else if (quantity_found) {
                    quantity = atol((const char*)event.data.scalar.value);
                    quantity_found = 0;
                }
                break;
            case YAML_STREAM_END_EVENT:
                goto end_parse;
            default:
                break;
        }

        yaml_event_delete(&event);
    }

end_parse:
    yaml_parser_delete(&parser);

    // Dummy prices for demonstration
    double price_per_unit = 0.0;
    switch(product_code) {
        case 101: price_per_unit = 9.99; break;
        case 202: price_per_unit = 4.50; break;
        case 303: price_per_unit = 19.99; break;
        default: price_per_unit = 0.0; break;
    }

    double total_price = quantity * price_per_unit;

    char* response = malloc(128);
    snprintf(response, 128, "total_price: %.2f", total_price);

    return response;
}

int main() {
    const char* yaml_input = "product_code: 101\nquantity: 5";
    char* result = get_price_for_product_code(yaml_input);
    if (result) {
        printf("%s\n", result);
        free(result);
    }
    return 0;
}