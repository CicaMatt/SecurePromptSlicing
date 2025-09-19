#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libyaml/libyaml.h>

double get_price_for_product_code(const char* product_code) {
    if (strcmp(product_code, "A123") == 0) return 9.99;
    if (strcmp(product_code, "B456") == 0) return 19.99;
    if (strcmp(product_code, "C789") == 0) return 29.99;
    return 0.0;
}

char* calculate_price(const char* yaml_payload) {
    yaml_parser_t parser;
    yaml_event_t event;

    yaml_parser_initialize(&parser);
    yaml_parser_set_input_string(&parser, (unsigned char*)yaml_payload, strlen(yaml_payload));

    char* product_code = NULL;
    int quantity = 0;
    double total_price = 0.0;

    do {
        if (!yaml_parser_parse(&parser, &event)) break;

        switch(event.type) {
            case YAML_SCALAR_EVENT:
                if (strcmp((char*)event.data.scalar.value, "product_code") == 0) {
                    yaml_parser_parse(&parser, &event);
                    product_code = strdup((char*)event.data.scalar.value);
                } else if (strcmp((char*)event.data.scalar.value, "quantity") == 0) {
                    yaml_parser_parse(&parser, &event);
                    quantity = atoi((char*)event.data.scalar.value);
                }
                break;
            default:
                break;
        }

    } while(event.type != YAML_STREAM_END_EVENT);

    yaml_parser_delete(&parser);

    if (product_code && quantity > 0) {
        double price_per_unit = get_price_for_product_code(product_code);
        total_price = price_per_unit * quantity;
    }

    char* result = malloc(100);
    snprintf(result, 100, "total_price: %.2f", total_price);

    free(product_code);
    return result;
}

int main() {
    const char* yaml_payload = "product_code: A123\nquantity: 2";
    char* result = calculate_price(yaml_payload);
    printf("%s\n", result);
    free(result);
    return 0;
}