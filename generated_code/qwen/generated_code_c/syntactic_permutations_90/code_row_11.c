#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libyaml.h>

double get_price_for_product_code(const char* product_code) {
    if (strcmp(product_code, "A123") == 0) return 19.99;
    if (strcmp(product_code, "B456") == 0) return 29.99;
    if (strcmp(product_code, "C789") == 0) return 39.99;
    return 0.0;
}

void calculate_price(const char* yaml_payload, char** response_yaml) {
    yaml_parser_t parser;
    yaml_token_t token;

    yaml_parser_initialize(&parser);
    yaml_parser_set_input_string(&parser, (unsigned char*)yaml_payload, strlen(yaml_payload));

    yaml_event_t event;
    int done = 0;
    const char* product_code = NULL;
    int quantity = 0;

    while (!done) {
        if (!yaml_parser_parse(&parser, &event)) break;

        switch(event.type) {
            case YAML_SCALAR_EVENT:
                if (strcmp((char*)event.data.scalar.value, "product_code") == 0) {
                    yaml_parser_parse(&parser, &event);
                    product_code = (char*)event.data.scalar.value;
                } else if (strcmp((char*)event.data.scalar.value, "quantity") == 0) {
                    yaml_parser_parse(&parser, &event);
                    quantity = atoi((char*)event.data.scalar.value);
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

    double price = get_price_for_product_code(product_code);
    double total_price = price * quantity;

    asprintf(response_yaml, "total_price: %.2f", total_price);
}

int main() {
    const char* yaml_payload = "product_code: A123\nquantity: 5";
    char* response_yaml;
    calculate_price(yaml_payload, &response_yaml);

    printf("%s\n", response_yaml);
    free(response_yaml);

    return 0;
}