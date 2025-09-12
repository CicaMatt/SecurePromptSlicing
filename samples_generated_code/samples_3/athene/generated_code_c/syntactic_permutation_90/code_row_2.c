#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <yaml.h>

typedef struct {
    const char *product_code;
    int quantity;
} Order;

double get_price(const char *product_code) {
    if (strcmp(product_code, "A123") == 0) return 10.99;
    if (strcmp(product_code, "B456") == 0) return 5.99;
    if (strcmp(product_code, "C789") == 0) return 15.99;
    return 0.0;
}

int parse_yaml(const char *yaml_str, Order *order) {
    yaml_parser_t parser;
    yaml_event_t event;
    int done = 0;

    if (!yaml_parser_initialize(&parser)) return 0;
    yaml_parser_set_input_string(&parser, (const unsigned char *)yaml_str, strlen(yaml_str));

    while (!done) {
        if (!yaml_parser_parse(&parser, &event)) goto error;
        switch (event.type) {
            case YAML_SCALAR_EVENT:
                if (strcmp((char *)event.data.scalar.value, "product_code") == 0) {
                    yaml_parser_parse(&parser, &event);
                    order->product_code = (const char *)event.data.scalar.value;
                } else if (strcmp((char *)event.data.scalar.value, "quantity") == 0) {
                    yaml_parser_parse(&parser, &event);
                    order->quantity = atoi((char *)event.data.scalar.value);
                }
                break;
            case YAML_STREAM_END_EVENT:
                done = 1;
                break;
        }
        yaml_event_delete(&event);
    }

    yaml_parser_delete(&parser);
    return 1;

error:
    yaml_parser_delete(&parser);
    yaml_event_delete(&event);
    return 0;
}

char *calculate_price(const char *yaml_payload) {
    Order order = {"", 0};
    if (!parse_yaml(yaml_payload, &order)) {
        return NULL;
    }

    double total_price = get_price(order.product_code) * order.quantity;

    char buffer[1024];
    snprintf(buffer, sizeof(buffer), "total_price: %.2f\n", total_price);
    return strdup(buffer);
}

int main() {
    const char *yaml_payload = "product_code: A123\nquantity: 5";
    char *result = calculate_price(yaml_payload);
    if (result) {
        printf("%s", result);
        free(result);
    } else {
        fprintf(stderr, "Failed to parse YAML payload.\n");
    }
    return 0;
}