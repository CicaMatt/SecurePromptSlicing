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

        if (event.type == YAML_SCALAR_EVENT) {
            const unsigned char *value = event.data.scalar.value;
            size_t length = event.data.scalar.length;

            if (strncmp((char *)value, "product_code", length) == 0) {
                yaml_parser_parse(&parser, &event);
                product_code = (const char *)event.data.scalar.value;
            } else if (strncmp((char *)value, "quantity", length) == 0) {
                yaml_parser_parse(&parser, &event);
                quantity = atoi((const char *)event.data.scalar.value);
            }
        }

        yaml_event_delete(&event);

        if (event.type == YAML_STREAM_END_EVENT) {
            break;
        }
    }

    // Example price lookup
    if (strcmp(product_code, "A123") == 0) {
        price = 10.5;
    } else if (strcmp(product_code, "B456") == 0) {
        price = 20.0;
    } else {
        goto error;
    }

    char *total_price_str = malloc(20);
    snprintf(total_price_str, 20, "%.2f", price * quantity);

    yaml_parser_free(&parser);
    return total_price_str;

error:
    yaml_parser_free(&parser);
    return NULL;
}