#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libyaml/yaml.h>

typedef struct {
    char *product_code;
    int quantity;
} Order;

double get_product_price(const char *product_code) {
    if (strcmp(product_code, "P001") == 0) return 9.99;
    else if (strcmp(product_code, "P002") == 0) return 4.50;
    else if (strcmp(product_code, "P003") == 0) return 15.00;
    return 0.0;
}

Order parse_yaml(const char *yaml_data) {
    yaml_parser_t parser;
    yaml_event_t event;
    Order order = {NULL, 0};
    int state = 0;

    yaml_parser_initialize(&parser);
    yaml_parser_set_input_string(&parser, (const unsigned char *)yaml_data, strlen(yaml_data));

    while (1) {
        if (!yaml_parser_parse(&parser, &event)) break;

        switch (event.type) {
            case YAML_SCALAR_EVENT:
                if (state == 1) {
                    order.product_code = strdup((char *)event.data.scalar.value);
                    state = 2;
                } else if (state == 3) {
                    order.quantity = atoi((char *)event.data.scalar.value);
                }
                break;
            case YAML_MAPPING_START_EVENT:
                state = 0;
                break;
            case YAML_KEY_EVENT:
                state++;
                break;
        }

        yaml_event_delete(&event);
    }

    yaml_parser_delete(&parser);
    return order;
}

char* calculate_price(const char *yaml_payload) {
    Order order = parse_yaml(yaml_payload);
    double price = get_product_price(order.product_code);
    double total_price = price * order.quantity;
    char *result = malloc(50);
    snprintf(result, 50, "%.2f", total_price);
    free(order.product_code);
    return result;
}

int main() {
    const char *yaml_input = "product_code: P001\nquantity: 3";
    char *price = calculate_price(yaml_input);
    printf("Total Price: %s\n", price);
    free(price);
    return 0;
}