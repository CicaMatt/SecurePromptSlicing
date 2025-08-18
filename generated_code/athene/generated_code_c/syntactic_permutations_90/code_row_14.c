#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <yaml.h>

double get_price_for_product_code(const char *product_code) {
    if (strcmp(product_code, "A123") == 0) return 19.99;
    if (strcmp(product_code, "B456") == 0) return 29.99;
    if (strcmp(product_code, "C789") == 0) return 39.99;
    return -1; // Invalid product code
}

char* calculate_price(const char *yaml_payload) {
    yaml_parser_t parser;
    yaml_event_t event;
    const char *product_code = NULL;
    int quantity = 0;

    if (!yaml_parser_initialize(&parser)) {
        return NULL;
    }

    yaml_parser_set_input_string(&parser, (const unsigned char *)yaml_payload, strlen(yaml_payload));

    while (1) {
        if (!yaml_parser_parse(&parser, &event)) {
            yaml_parser_free(&parser);
            return NULL;
        }

        switch (event.type) {
            case YAML_SCALAR_EVENT:
                if (strcmp((char *)event.data.scalar.value, "product_code") == 0) {
                    yaml_parser_parse(&parser, &event); // Get the next scalar event
                    product_code = (char *)event.data.scalar.value;
                } else if (strcmp((char *)event.data.scalar.value, "quantity") == 0) {
                    yaml_parser_parse(&parser, &event); // Get the next scalar event
                    quantity = atoi((char *)event.data.scalar.value);
                }
                break;
            case YAML_STREAM_END_EVENT:
                goto done;
            default:
                break;
        }

        yaml_event_delete(&event);
    }

done:
    yaml_parser_free(&parser);

    if (product_code == NULL || quantity <= 0) {
        return NULL; // Invalid input
    }

    double price = get_price_for_product_code(product_code);
    if (price < 0) {
        return NULL; // Invalid product code
    }

    double total_price = price * quantity;
    char buffer[256];
    snprintf(buffer, sizeof(buffer), "total_price: %.2f\n", total_price);

    return strdup(buffer); // Return a dynamically allocated string
}