#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libyaml.h>

double get_price_for_product_code(const char *product_code) {
    if (strcmp(product_code, "A123") == 0) return 9.99;
    if (strcmp(product_code, "B456") == 0) return 19.99;
    if (strcmp(product_code, "C789") == 0) return 29.99;
    return -1; // Product code not found
}

int parse_yaml_payload(const char *yaml_payload, char **product_code, int *quantity) {
    yaml_parser_t parser;
    yaml_event_t event;

    if (!yaml_parser_initialize(&parser)) {
        fprintf(stderr, "Failed to initialize the YAML parser.\n");
        return 0;
    }

    yaml_parser_set_input_string(&parser, (unsigned char *)yaml_payload, strlen(yaml_payload));

    do {
        if (!yaml_parser_parse(&parser, &event)) {
            fprintf(stderr, "Parser error %d\n", parser.error);
            yaml_event_delete(&event);
            yaml_parser_delete(&parser);
            return 0;
        }

        switch (event.type) {
            case YAML_SCALAR_EVENT:
                if (strcmp((char *)event.data.scalar.value, "product_code") == 0) {
                    yaml_event_delete(&event);
                    if (!yaml_parser_parse(&parser, &event)) break;
                    *product_code = strdup((char *)event.data.scalar.value);
                } else if (strcmp((char *)event.data.scalar.value, "quantity") == 0) {
                    yaml_event_delete(&event);
                    if (!yaml_parser_parse(&parser, &event)) break;
                    *quantity = atoi((char *)event.data.scalar.value);
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

void calculate_price(const char *yaml_payload) {
    char *product_code = NULL;
    int quantity = 0;

    if (!parse_yaml_payload(yaml_payload, &product_code, &quantity)) {
        fprintf(stderr, "Failed to parse YAML payload.\n");
        return;
    }

    double price_per_unit = get_price_for_product_code(product_code);
    if (price_per_unit == -1) {
        printf("Product code not found.\n");
        free(product_code);
        return;
    }

    double total_price = price_per_unit * quantity;

    // Output the result as a YAML payload
    printf("total_price: %.2f\n", total_price);

    free(product_code);
}

int main() {
    const char *yaml_payload = "product_code: A123\nquantity: 3";
    calculate_price(yaml_payload);
    return 0;
}