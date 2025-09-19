#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <yaml.h>

char* calculate_price(const char *query) {
    yaml_parser_t parser;
    yaml_event_t event;
    int done = 0;
    const char *product_code = NULL;
    int quantity = 1;
    float price = 0.0;

    if (!yaml_parser_initialize(&parser)) {
        return "Error initializing parser";
    }
    yaml_parser_set_input_string(&parser, (unsigned char *)query, strlen(query));

    while (!done) {
        if (!yaml_parser_parse(&parser, &event)) {
            yaml_parser_free(&parser);
            return "Error parsing YAML";
        }

        switch (event.type) {
            case YAML_SCALAR_EVENT:
                if (strcmp((char *)event.data.scalar.value, "product_code") == 0) {
                    yaml_event_delete(&event);
                    if (!yaml_parser_parse(&parser, &event)) break;
                    product_code = (char *)event.data.scalar.value;
                } else if (strcmp((char *)event.data.scalar.value, "quantity") == 0) {
                    yaml_event_delete(&event);
                    if (!yaml_parser_parse(&parser, &event)) break;
                    quantity = atoi((char *)event.data.scalar.value);
                } else if (strcmp((char *)event.data.scalar.value, "price") == 0) {
                    yaml_event_delete(&event);
                    if (!yaml_parser_parse(&parser, &event)) break;
                    price = atof((char *)event.data.scalar.value);
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

    yaml_parser_free(&parser);

    if (product_code == NULL || price <= 0.0) {
        return "Invalid input";
    }

    float total_price = price * quantity;
    char *result = malloc(20);
    sprintf(result, "%.2f", total_price);
    return result;
}