#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libyaml.h>

char* calculate_price(const char* yaml_payload) {
    yaml_parser_t parser;
    yaml_event_t event;

    if (!yaml_parser_initialize(&parser)) {
        fprintf(stderr, "Parser initialization failed\n");
        return NULL;
    }

    yaml_parser_set_input_string(&parser, (unsigned char*)yaml_payload, strlen(yaml_payload));

    int product_found = 0;
    int quantity_found = 0;
    double price = 0.0;
    int quantity = 0;

    while (1) {
        if (!yaml_parser_parse(&parser, &event)) {
            fprintf(stderr, "Parser error %d\n", parser.error);
            yaml_event_delete(&event);
            yaml_parser_delete(&parser);
            return NULL;
        }

        switch (event.type) {
            case YAML_SCALAR_EVENT:
                if (!product_found && strcmp((char*)event.data.scalar.value, "product") == 0) {
                    product_found = 1;
                } else if (product_found && !quantity_found) {
                    price = atof((char*)event.data.scalar.value);
                    product_found = 0;
                } else if (!quantity_found && strcmp((char*)event.data.scalar.value, "quantity") == 0) {
                    quantity_found = 1;
                } else if (quantity_found) {
                    quantity = atoi((char*)event.data.scalar.value);
                    quantity_found = 0;
                }
                break;
            case YAML_STREAM_END_EVENT:
                goto out;
            default:
                break;
        }

        yaml_event_delete(&event);
    }

out:
    yaml_parser_delete(&parser);

    double total_price = price * quantity;
    char* result = malloc(256);
    snprintf(result, 256, "%.2f", total_price);
    return result;
}

int main() {
    const char* yaml_payload = "product: 19.99\nquantity: 3";
    char* price = calculate_price(yaml_payload);
    if (price) {
        printf("Total Price: %s\n", price);
        free(price);
    }
    return 0;
}