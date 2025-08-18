#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <yaml.h>

typedef struct {
    char *product_code;
    int quantity;
} Order;

double get_product_price(const char *product_code) {
    if (strcmp(product_code, "A") == 0) return 1.25;
    if (strcmp(product_code, "B") == 0) return 2.50;
    if (strcmp(product_code, "C") == 0) return 3.75;
    return -1; // Invalid product code
}

double calculate_price(const char *yaml_payload) {
    yaml_parser_t parser;
    yaml_event_t event;
    Order order = {NULL, 0};
    double total_price = 0;

    if (!yaml_parser_initialize(&parser)) {
        exit(1);
    }
    yaml_parser_set_input_string(&parser, (const unsigned char *)yaml_payload, strlen(yaml_payload));

    while (1) {
        if (!yaml_parser_parse(&parser, &event)) {
            goto cleanup;
        }

        switch (event.type) {
            case YAML_SCALAR_EVENT:
                if (strcmp((char *)event.data.scalar.value, "product_code") == 0) {
                    yaml_parser_parse(&parser, &event);
                    order.product_code = strdup((char *)event.data.scalar.value);
                } else if (strcmp((char *)event.data.scalar.value, "quantity") == 0) {
                    yaml_parser_parse(&parser, &event);
                    order.quantity = atoi((char *)event.data.scalar.value);
                }
                break;
            case YAML_STREAM_END_EVENT:
                goto parse_done;
            default:
                break;
        }

        yaml_event_delete(&event);
    }

parse_done:
    if (order.product_code && order.quantity > 0) {
        double price_per_unit = get_product_price(order.product_code);
        if (price_per_unit != -1) {
            total_price = price_per_unit * order.quantity;
        }
    }

cleanup:
    yaml_parser_cleanup(&parser);
    free(order.product_code);
    return total_price;
}