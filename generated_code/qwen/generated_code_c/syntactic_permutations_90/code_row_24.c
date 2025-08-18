#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <yaml.h>

double get_price_for_product_code(const char* product_code) {
    if (strcmp(product_code, "A1") == 0) return 9.99;
    if (strcmp(product_code, "B2") == 0) return 4.99;
    if (strcmp(product_code, "C3") == 0) return 14.99;
    return 0.0;
}

void parse_yaml(const char* yaml_data, char** product_code, int* quantity) {
    yaml_parser_t parser;
    yaml_event_t event;

    yaml_parser_initialize(&parser);
    yaml_parser_set_input_string(&parser, (unsigned char*)yaml_data, strlen(yaml_data));

    do {
        if (!yaml_parser_parse(&parser, &event)) break;

        switch(event.type) {
            case YAML_SCALAR_EVENT:
                if (strcmp((const char*)event.data.scalar.value, "product_code") == 0) {
                    yaml_parser_parse(&parser, &event);
                    *product_code = strdup((const char*)event.data.scalar.value);
                } else if (strcmp((const char*)event.data.scalar.value, "quantity") == 0) {
                    yaml_parser_parse(&parser, &event);
                    *quantity = atoi((const char*)event.data.scalar.value);
                }
                break;
            default:
                break;
        }

        yaml_event_delete(&event);
    } while(event.type != YAML_STREAM_END_EVENT);

    yaml_parser_delete(&parser);
}

void calculate_price(const char* yaml_data, char* result) {
    char* product_code = NULL;
    int quantity = 0;

    parse_yaml(yaml_data, &product_code, &quantity);

    double price = get_price_for_product_code(product_code);
    double total_price = price * quantity;

    sprintf(result, "total_price: %.2f", total_price);

    free(product_code);
}

int main() {
    const char* yaml_input = "product_code: A1\nquantity: 3";
    char result[50];

    calculate_price(yaml_input, result);

    printf("%s\n", result);

    return 0;
}