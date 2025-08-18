#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libyaml/parser.h>

#define MAX_BUFFER 1024

double get_price_for_product_code(const char* product_code) {
    // Mock function to return price based on product code
    if (strcmp(product_code, "A") == 0) return 9.99;
    if (strcmp(product_code, "B") == 0) return 14.50;
    if (strcmp(product_code, "C") == 0) return 29.95;
    return 0.0;
}

int parse_yaml(const char* yaml_data, char** product_code, int* quantity) {
    yaml_parser_t parser;
    yaml_event_t event;

    yaml_parser_initialize(&parser);
    yaml_parser_set_input_string(&parser, (const unsigned char*)yaml_data, strlen(yaml_data));

    do {
        if (!yaml_parser_parse(&parser, &event))
            break;

        switch (event.type) {
            case YAML_SCALAR_EVENT:
                if (strcmp((char*)event.data.scalar.value, "product_code") == 0) {
                    yaml_parser_parse(&parser, &event);
                    *product_code = strdup((char*)event.data.scalar.value);
                } else if (strcmp((char*)event.data.scalar.value, "quantity") == 0) {
                    yaml_parser_parse(&parser, &event);
                    *quantity = atoi((char*)event.data.scalar.value);
                }
                break;
            default:
                break;
        }

        yaml_event_delete(&event);

    } while (1);

    yaml_parser_delete(&parser);

    return (*product_code && *quantity) ? 0 : -1;
}

void calculate_price(const char* yaml_data, char* response_buffer) {
    char* product_code = NULL;
    int quantity = 0;

    if (parse_yaml(yaml_data, &product_code, &quantity) == 0) {
        double price_per_unit = get_price_for_product_code(product_code);
        double total_price = price_per_unit * quantity;
        snprintf(response_buffer, MAX_BUFFER, "total_price: %.2f", total_price);
    } else {
        snprintf(response_buffer, MAX_BUFFER, "error: Invalid YAML payload");
    }

    if (product_code) free(product_code);
}

int main() {
    char yaml_data[] = "product_code: A\nquantity: 3";
    char response[MAX_BUFFER];

    calculate_price(yaml_data, response);

    printf("%s\n", response);

    return 0;
}