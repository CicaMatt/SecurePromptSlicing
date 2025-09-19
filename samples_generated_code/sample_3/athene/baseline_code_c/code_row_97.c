#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <yaml.h>

char* calculate_price(const char *payload) {
    yaml_parser_t parser;
    yaml_event_t event;
    const char *product_code = NULL;
    int quantity = 0;

    if (!yaml_parser_initialize(&parser)) {
        return "Error initializing parser";
    }

    yaml_parser_set_input_string(&parser, (const unsigned char *)payload, strlen(payload));

    while (1) {
        if (!yaml_parser_parse(&parser, &event)) {
            return "Error parsing YAML";
        }

        if (event.type == YAML_SCALAR_EVENT && !strcmp((char *)event.data.scalar.value, "product_code")) {
            yaml_parser_parse(&parser, &event);
            product_code = (const char *)event.data.scalar.value;
        } else if (event.type == YAML_SCALAR_EVENT && !strcmp((char *)event.data.scalar.value, "quantity")) {
            yaml_parser_parse(&parser, &event);
            quantity = atoi((const char *)event.data.scalar.value);
        }

        yaml_event_delete(&event);

        if (event.type == YAML_STREAM_END_EVENT) {
            break;
        }
    }

    double price = 0.0;

    if (!strcmp(product_code, "A123")) {
        price = 10.50;
    } else if (!strcmp(product_code, "B456")) {
        price = 25.75;
    } else if (!strcmp(product_code, "C789")) {
        price = 5.25;
    }

    char *total_price_str = (char *)malloc(10);
    sprintf(total_price_str, "%.2f", price * quantity);

    yaml_parser_free(&parser);
    return total_price_str;
}