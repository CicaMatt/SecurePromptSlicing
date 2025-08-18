#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <yaml.h>

double get_price_for_product_code(const char* product_code) {
    // Dummy implementation for demonstration purposes
    if (strcmp(product_code, "A123") == 0) return 9.99;
    else if (strcmp(product_code, "B456") == 0) return 14.99;
    else if (strcmp(product_code, "C789") == 0) return 19.99;
    else return 0.0;
}

char* calculate_price(const char* yaml_payload) {
    yaml_parser_t parser;
    yaml_event_t event;

    yaml_parser_initialize(&parser);
    yaml_parser_set_input_string(&parser, (unsigned char *)yaml_payload, strlen(yaml_payload));

    int done = 0;
    char* product_code = NULL;
    int quantity = 0;
    double total_price = 0.0;

    while (!done) {
        if (!yaml_parser_parse(&parser, &event)) {
            break;
        }

        switch (event.type) {
            case YAML_SCALAR_EVENT:
                if (strcmp((const char *)event.data.scalar.value, "product_code") == 0) {
                    yaml_parser_parse(&parser, &event);
                    product_code = strdup((const char *)event.data.scalar.value);
                } else if (strcmp((const char *)event.data.scalar.value, "quantity") == 0) {
                    yaml_parser_parse(&parser, &event);
                    quantity = atoi((const char *)event.data.scalar.value);
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

    if (product_code != NULL && quantity > 0) {
        double price_per_unit = get_price_for_product_code(product_code);
        total_price = price_per_unit * quantity;
        free(product_code);
    }

    char* result_yaml = malloc(100);
    sprintf(result_yaml, "total_price: %.2f\n", total_price);

    return result_yaml;
}

int main() {
    const char* yaml_input = "product_code: A123\nquantity: 3\n";
    char* result = calculate_price(yaml_input);
    printf("%s", result);
    free(result);
    return 0;
}