#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <yaml.h>

typedef struct {
    char *product_code;
    int quantity;
} Order;

double get_price_for_product_code(const char *code) {
    if (strcmp(code, "A123") == 0) return 10.5;
    if (strcmp(code, "B456") == 0) return 20.75;
    if (strcmp(code, "C789") == 0) return 30.0;
    return -1.0; // Invalid product code
}

double calculate_price(const char *yaml_payload, char **result_yaml) {
    yaml_parser_t parser;
    yaml_event_t event;
    Order order = { NULL, 0 };
    int key = 0;

    if (!yaml_parser_initialize(&parser)) return -1.0;
    yaml_parser_set_input_string(&parser, (const unsigned char *)yaml_payload, strlen(yaml_payload));

    while (1) {
        if (!yaml_parser_parse(&parser, &event)) break;

        switch (event.type) {
            case YAML_SCALAR_EVENT:
                if (key == 0 && strcmp((char *)event.data.scalar.value, "product_code") == 0) {
                    key = 1;
                } else if (key == 1) {
                    order.product_code = strdup((char *)event.data.scalar.value);
                    key++;
                } else if (key == 2 && strcmp((char *)event.data.scalar.value, "quantity") == 0) {
                    key = 3;
                } else if (key == 3) {
                    char *endptr;
                    order.quantity = (int)strtol((char *)event.data.scalar.value, &endptr, 10);
                    if (*endptr != '\0') return -1.0; // Invalid quantity
                    key++;
                }
                break;
            default:
                break;
        }

        yaml_event_delete(&event);

        if (key == 4) break;
    }

    yaml_parser_cleanup(&parser);

    double price_per_unit = get_price_for_product_code(order.product_code);
    double total_price = price_per_unit * order.quantity;

    char buffer[256];
    snprintf(buffer, sizeof(buffer), "total_price: %.2f", total_price);

    *result_yaml = strdup(buffer);

    free(order.product_code);

    return total_price;
}

int main() {
    const char *yaml_payload = "product_code: A123\nquantity: 5";
    char *result_yaml;
    double total_price = calculate_price(yaml_payload, &result_yaml);
    printf("YAML Response: %s\n", result_yaml);
    free(result_yaml);

    return 0;
}