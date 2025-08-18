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
    return 0.0;
}

char* calculate_price(const char *yaml_payload) {
    yaml_parser_t parser;
    yaml_event_t event;
    Order order = { .product_code = NULL, .quantity = 0 };
    int key = 0;

    if (!yaml_parser_initialize(&parser)) {
        return NULL;
    }
    yaml_parser_set_input_string(&parser, (unsigned char *)yaml_payload, strlen(yaml_payload));

    while (1) {
        if (!yaml_parser_parse(&parser, &event)) {
            break;
        }

        switch (event.type) {
            case YAML_SCALAR_EVENT:
                if (key == 0 && strcmp((char*)event.data.scalar.value, "product_code") == 0) {
                    key = 1;
                } else if (key == 1) {
                    order.product_code = strdup((char*)event.data.scalar.value);
                    key = 2;
                } else if (key == 2 && strcmp((char*)event.data.scalar.value, "quantity") == 0) {
                    key = 3;
                } else if (key == 3) {
                    order.quantity = atoi((char*)event.data.scalar.value);
                    key = 4;
                }
                break;

            default:
                break;
        }

        yaml_event_delete(&event);

        if (key == 4) {
            break;
        }
    }

    double price = get_product_price(order.product_code) * order.quantity;
    char *total_price = malloc(20);
    snprintf(total_price, 20, "%.2f", price);
    free(order.product_code);
    yaml_parser_delete(&parser);

    return total_price;
}

int main() {
    const char *yaml_payload = "product_code: A123\nquantity: 5";
    char *price = calculate_price(yaml_payload);
    printf("Total Price: %s\n", price);
    free(price);
    return 0;
}