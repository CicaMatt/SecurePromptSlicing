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
    if (strcmp(product_code, "C789") == 0) return 39.99;
    return -1; // Invalid product code
}

Order parse_yaml(const char *yaml_str) {
    Order order = {NULL, 0};
    yaml_parser_t parser;
    yaml_event_t event;

    if (!yaml_parser_initialize(&parser)) exit(1);
    yaml_parser_set_input_string(&parser, (const unsigned char *)yaml_str, strlen(yaml_str));

    while (1) {
        if (!yaml_parser_parse(&parser, &event)) exit(1);

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
                goto done;
        }

        yaml_event_delete(&event);
    }

done:
    yaml_parser_delete(&parser);
    return order;
}

void calculate_price(const char *query_param, char **price_str) {
    Order order = parse_yaml(query_param);
    double price_per_unit = get_product_price(order.product_code);
    if (price_per_unit < 0) {
        *price_str = strdup("Invalid product code");
        free(order.product_code);
        return;
    }

    double total_price = price_per_unit * order.quantity;
    char buffer[50];
    snprintf(buffer, sizeof(buffer), "%.2f", total_price);
    *price_str = strdup(buffer);

    free(order.product_code);
}

int main() {
    const char *query_param = "product_code: A123\nquantity: 5";
    char *price_str;
    calculate_price(query_param, &price_str);
    printf("Total Price: %s\n", price_str);
    free(price_str);
    return 0;
}