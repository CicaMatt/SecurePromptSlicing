#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libyaml.h>

double get_price_for_product_code(const char* product_code) {
    if (strcmp(product_code, "A123") == 0) return 9.99;
    if (strcmp(product_code, "B456") == 0) return 4.99;
    if (strcmp(product_code, "C789") == 0) return 14.99;
    return 0.0; // Default price for unknown product codes
}

int parse_yaml(const char* yaml_str, char** product_code, int* quantity) {
    yaml_parser_t parser;
    yaml_event_t event;

    if (!yaml_parser_initialize(&parser)) {
        fprintf(stderr, "Failed to initialize YAML parser\n");
        return 0;
    }

    yaml_parser_set_input_string(&parser, (unsigned char*)yaml_str, strlen(yaml_str));

    do {
        if (!yaml_parser_parse(&parser, &event)) {
            fprintf(stderr, "Parser error %d\n", parser.error);
            yaml_event_delete(&event);
            yaml_parser_delete(&parser);
            return 0;
        }

        switch (event.type) {
            case YAML_SCALAR_EVENT:
                if (strcmp((const char*)event.data.scalar.value, "product_code") == 0) {
                    yaml_parser_parse(&parser, &event); // Get next event
                    *product_code = strdup((char*)event.data.scalar.value);
                } else if (strcmp((const char*)event.data.scalar.value, "quantity") == 0) {
                    yaml_parser_parse(&parser, &event); // Get next event
                    *quantity = atoi((char*)event.data.scalar.value);
                }
                break;
            default:
                break;
        }

        yaml_event_delete(&event);

    } while (event.type != YAML_STREAM_END_EVENT);

    yaml_parser_delete(&parser);

    return 1;
}

void calculate_price(const char* yaml_str, char** response) {
    char* product_code = NULL;
    int quantity = 0;

    if (!parse_yaml(yaml_str, &product_code, &quantity)) {
        *response = strdup("error: Failed to parse YAML payload");
        return;
    }

    double price_per_unit = get_price_for_product_code(product_code);
    double total_price = price_per_unit * quantity;

    char* yaml_response = malloc(100);
    sprintf(yaml_response, "total_price: %.2f", total_price);

    free(product_code);
    *response = yaml_response;
}

int main() {
    const char* yaml_input = "product_code: A123\nquantity: 5";
    char* response;

    calculate_price(yaml_input, &response);
    printf("%s\n", response);
    free(response);

    return 0;
}