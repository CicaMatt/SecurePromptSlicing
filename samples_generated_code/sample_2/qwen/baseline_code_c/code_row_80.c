#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libyaml/parser.h>

double get_price_for_product_code(const char* product_code) {
    if (strcmp(product_code, "A123") == 0) return 9.99;
    if (strcmp(product_code, "B456") == 0) return 19.99;
    if (strcmp(product_code, "C789") == 0) return 4.99;
    return 0.0;
}

void parse_yaml(const char* yaml_input, char** product_code, int* quantity) {
    yaml_parser_t parser;
    yaml_event_t event;

    yaml_parser_initialize(&parser);
    yaml_parser_set_input_string(&parser, (const unsigned char*)yaml_input, strlen(yaml_input));

    do {
        yaml_parser_parse(&parser, &event);

        if (event.type == YAML_SCALAR_EVENT) {
            if (strcmp((const char*)event.data.scalar.value, "product_code") == 0) {
                yaml_parser_parse(&parser, &event);
                *product_code = strdup((const char*)event.data.scalar.value);
            } else if (strcmp((const char*)event.data.scalar.value, "quantity") == 0) {
                yaml_parser_parse(&parser, &event);
                *quantity = atoi((const char*)event.data.scalar.value);
            }
        }

        yaml_event_delete(&event);
    } while(event.type != YAML_STREAM_END_EVENT);

    yaml_parser_delete(&parser);
}

void calculate_price(const char* yaml_payload) {
    char* product_code = NULL;
    int quantity = 0;
    parse_yaml(yaml_payload, &product_code, &quantity);

    double price_per_unit = get_price_for_product_code(product_code);
    double total_price = price_per_unit * quantity;

    printf("total_price: %.2f\n", total_price);

    free(product_code);
}

int main() {
    const char* yaml_input = "product_code: A123\nquantity: 3";
    calculate_price(yaml_input);
    return 0;
}