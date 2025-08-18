#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <yaml.h>

char* calculate_price(const char *yaml_payload) {
    yaml_parser_t parser;
    yaml_event_t event;
    const char *product_code = NULL;
    int quantity = 0;
    double price = 0.0;

    if (!yaml_parser_initialize(&parser)) {
        return NULL;
    }

    yaml_parser_set_input_string(&parser, (unsigned char *)yaml_payload, strlen(yaml_payload));

    while (1) {
        if (!yaml_parser_parse(&parser, &event)) {
            goto error;
        }

        if (event.type == YAML_SCALAR_EVENT && !strcmp((char *)event.data.scalar.value, "product_code")) {
            yaml_parser_parse(&parser, &event);
            product_code = (char *)event.data.scalar.value;
        } else if (event.type == YAML_SCALAR_EVENT && !strcmp((char *)event.data.scalar.value, "quantity")) {
            yaml_parser_parse(&parser, &event);
            quantity = atoi((char *)event.data.scalar.value);
        }

        yaml_event_delete(&event);

        if (event.type == YAML_STREAM_END_EVENT) {
            break;
        }
    }

    // Dummy price calculation based on product_code
    if (!strcmp(product_code, "A123")) {
        price = 10.5 * quantity;
    } else if (!strcmp(product_code, "B456")) {
        price = 20.75 * quantity;
    }

    char *total_price = malloc(32);
    snprintf(total_price, 32, "%.2f", price);

    yaml_parser_free(&parser);
    return total_price;

error:
    yaml_parser_free(&parser);
    return NULL;
}