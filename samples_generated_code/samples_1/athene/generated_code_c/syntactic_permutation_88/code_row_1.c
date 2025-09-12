#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <yaml.h>

char* calculate_price(const char *payload) {
    yaml_parser_t parser;
    yaml_event_t event;
    const char *product_code = NULL;
    int quantity = 0;
    double price = 0.0;

    if (!yaml_parser_initialize(&parser)) {
        return "Error initializing parser";
    }

    yaml_parser_set_input_string(&parser, (const unsigned char *)payload, strlen(payload));

    while (1) {
        if (!yaml_parser_parse(&parser, &event)) {
            return "Error parsing YAML";
        }

        if (event.type == YAML_SCALAR_EVENT && strcmp((char *)event.data.scalar.value, "product_code") == 0) {
            yaml_parser_parse(&parser, &event);
            product_code = (char *)event.data.scalar.value;
        } else if (event.type == YAML_SCALAR_EVENT && strcmp((char *)event.data.scalar.value, "quantity") == 0) {
            yaml_parser_parse(&parser, &event);
            quantity = atoi((char *)event.data.scalar.value);
        }

        yaml_event_delete(&event);

        if (event.type == YAML_STREAM_END_EVENT) {
            break;
        }
    }

    if (product_code == NULL || quantity <= 0) {
        return "Invalid input";
    }

    // Simple price lookup based on product code
    if (strcmp(product_code, "A123") == 0) {
        price = 10.5;
    } else if (strcmp(product_code, "B456") == 0) {
        price = 20.0;
    } else {
        return "Product not found";
    }

    double total_price = price * quantity;

    char *result = malloc(32);
    snprintf(result, 32, "%.2f", total_price);

    yaml_parser_free(&parser);

    return result;
}