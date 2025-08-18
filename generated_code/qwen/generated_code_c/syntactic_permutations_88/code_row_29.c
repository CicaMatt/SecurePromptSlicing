#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <yaml.h>

typedef struct {
    char *product_code;
    int quantity;
} Order;

double get_product_price(const char* product_code) {
    // This function would normally query a database or another service to get the price of a product
    if (strcmp(product_code, "A123") == 0) return 9.99;
    if (strcmp(product_code, "B456") == 0) return 19.99;
    return 0.0;
}

char* calculate_price(const char *yaml_payload) {
    yaml_parser_t parser;
    yaml_event_t event;

    yaml_parser_initialize(&parser);
    yaml_parser_set_input_string(&parser, (const unsigned char *)yaml_payload, strlen(yaml_payload));

    Order order = {NULL, 0};
    int done = 0;

    while (!done) {
        if (!yaml_parser_parse(&parser, &event)) {
            break;
        }

        switch(event.type) {
            case YAML_SCALAR_EVENT:
                if (strcmp((const char*)event.data.scalar.value, "product_code") == 0) {
                    yaml_parser_parse(&parser, &event);
                    order.product_code = strdup((char *)event.data.scalar.value);
                } else if (strcmp((const char*)event.data.scalar.value, "quantity") == 0) {
                    yaml_parser_parse(&parser, &event);
                    order.quantity = atoi((char *)event.data.scalar.value);
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

    yaml_parser_delete(&parser);

    double price = get_product_price(order.product_code);
    double total_price = price * order.quantity;

    char* result = malloc(20); // Enough to hold a formatted double value
    sprintf(result, "%.2f", total_price);

    free(order.product_code);
    return result;
}

int main() {
    const char *yaml_payload = "product_code: A123\nquantity: 5";
    char *total_price = calculate_price(yaml_payload);
    printf("Total Price: %s\n", total_price);
    free(total_price);
    return 0;
}