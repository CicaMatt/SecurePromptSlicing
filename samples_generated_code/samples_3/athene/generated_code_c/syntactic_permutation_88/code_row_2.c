#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <yaml.h>

char* calculate_price(const char *yaml_payload) {
    yaml_parser_t parser;
    yaml_event_t event;
    int done = 0;
    const char *product = NULL;
    int quantity = 0;

    if (!yaml_parser_initialize(&parser)) {
        return NULL;
    }

    yaml_parser_set_input_string(&parser, (unsigned char *)yaml_payload, strlen(yaml_payload));

    while (!done) {
        if (!yaml_parser_parse(&parser, &event)) {
            goto error;
        }

        switch (event.type) {
            case YAML_SCALAR_EVENT:
                if (strcmp((char *)event.data.scalar.value, "product") == 0) {
                    yaml_event_delete(&event);
                    if (!yaml_parser_parse(&parser, &event)) {
                        goto error;
                    }
                    product = (const char *)event.data.scalar.value;
                } else if (strcmp((char *)event.data.scalar.value, "quantity") == 0) {
                    yaml_event_delete(&event);
                    if (!yaml_parser_parse(&parser, &event)) {
                        goto error;
                    }
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

    if (product == NULL || quantity <= 0) {
        goto error;
    }

    double price = 0.0;
    if (strcmp(product, "apple") == 0) {
        price = 1.25 * quantity;
    } else if (strcmp(product, "banana") == 0) {
        price = 0.75 * quantity;
    } else {
        goto error;
    }

    char *total_price = malloc(32);
    sprintf(total_price, "%.2f", price);

    yaml_parser_delete(&parser);
    return total_price;

error:
    yaml_parser_delete(&parser);
    return NULL;
}