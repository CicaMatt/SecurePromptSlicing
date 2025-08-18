#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <yaml.h>

typedef struct {
    char *product_code;
    int quantity;
} Order;

double get_product_price(const char *product_code) {
    if (strcmp(product_code, "A123") == 0) return 19.99;
    if (strcmp(product_code, "B456") == 0) return 29.99;
    if (strcmp(product_code, "C789") == 0) return 9.99;
    return -1; // Invalid product code
}

Order parse_yaml(const char *yaml_str) {
    Order order = {0};
    yaml_parser_t parser;
    yaml_event_t event;

    if (!yaml_parser_initialize(&parser)) exit(1);
    yaml_parser_set_input_string(&parser, (const unsigned char *)yaml_str, strlen(yaml_str));

    while (1) {
        if (!yaml_parser_parse(&parser, &event)) exit(1);

        if (event.type == YAML_SCALAR_EVENT) {
            const char *key = (const char *)event.data.scalar.value;
            yaml_event_t value_event;

            if (!yaml_parser_parse(&parser, &value_event)) exit(1);
            if (value_event.type != YAML_SCALAR_EVENT) continue;

            if (strcmp(key, "product_code") == 0) {
                order.product_code = strdup((const char *)value_event.data.scalar.value);
            } else if (strcmp(key, "quantity") == 0) {
                order.quantity = atoi((const char *)value_event.data.scalar.value);
            }

            yaml_event_delete(&value_event);
        }

        if (event.type == YAML_STREAM_END_EVENT) break;
        yaml_event_delete(&event);
    }

    yaml_parser_delete(&parser);
    return order;
}

double calculate_price(const char *yaml_str) {
    Order order = parse_yaml(yaml_str);
    double price_per_unit = get_product_price(order.product_code);
    if (price_per_unit == -1) {
        fprintf(stderr, "Invalid product code: %s\n", order.product_code);
        free(order.product_code);
        return -1;
    }
    double total_price = price_per_unit * order.quantity;
    free(order.product_code);
    return total_price;
}

int main() {
    const char *yaml_str = "product_code: A123\nquantity: 5";
    double total_price = calculate_price(yaml_str);
    if (total_price != -1) {
        printf("Total Price: %.2f\n", total_price);
    }
    return 0;
}