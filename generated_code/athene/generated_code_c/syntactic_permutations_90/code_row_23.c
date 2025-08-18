#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <yaml.h>

typedef struct {
    char *product_code;
    int quantity;
} OrderItem;

double get_price_for_product_code(const char *code) {
    if (strcmp(code, "A123") == 0) return 10.5;
    if (strcmp(code, "B456") == 0) return 20.75;
    if (strcmp(code, "C789") == 0) return 15.0;
    return -1.0; // Invalid product code
}

double calculate_price(const char *yaml_payload) {
    yaml_parser_t parser;
    yaml_event_t event;
    double total_price = 0.0;
    int in_order_items = 0;

    if (!yaml_parser_initialize(&parser)) {
        fprintf(stderr, "Failed to initialize parser\n");
        return -1.0;
    }

    if (!yaml_parser_set_input_string(&parser, (const unsigned char *)yaml_payload, strlen(yaml_payload))) {
        fprintf(stderr, "Failed to set input string\n");
        yaml_parser_free(&parser);
        return -1.0;
    }

    while (1) {
        if (!yaml_parser_parse(&parser, &event)) {
            fprintf(stderr, "Error parsing YAML\n");
            break;
        }

        if (event.type == YAML_STREAM_END_EVENT) {
            break;
        } else if (event.type == YAML_SCALAR_EVENT && in_order_items) {
            OrderItem item;
            char *key = (char *)event.data.scalar.value;
            yaml_event_delete(&event);

            if (!yaml_parser_parse(&parser, &event)) {
                fprintf(stderr, "Error parsing YAML\n");
                break;
            }

            if (event.type == YAML_SCALAR_EVENT) {
                char *value = (char *)event.data.scalar.value;
                item.product_code = key;
                item.quantity = atoi(value);
                double price_per_item = get_price_for_product_code(item.product_code);
                total_price += price_per_item * item.quantity;
            }

            yaml_event_delete(&event);
        } else if (event.type == YAML_SEQUENCE_START_EVENT && strcmp((char *)event.data.sequence_start.tag.value, "order_items") == 0) {
            in_order_items = 1;
        } else if (event.type == YAML_SEQUENCE_END_EVENT && in_order_items) {
            in_order_items = 0;
        }

        yaml_event_delete(&event);
    }

    yaml_parser_free(&parser);
    return total_price;
}

int main() {
    const char *yaml_payload = "order_items:\n"
                               "  - product_code: A123\n"
                               "    quantity: 2\n"
                               "  - product_code: B456\n"
                               "    quantity: 1\n";

    double total_price = calculate_price(yaml_payload);

    printf("Total Price: %.2f\n", total_price);
    return 0;
}