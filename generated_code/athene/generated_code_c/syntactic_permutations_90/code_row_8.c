#include <stdio.h>
#include <string.h>
#include <yaml.h>

typedef struct {
    char *product_code;
    int quantity;
} Order;

double get_price_for_product_code(const char *code) {
    if (strcmp(code, "A123") == 0) return 10.5;
    if (strcmp(code, "B456") == 0) return 20.0;
    if (strcmp(code, "C789") == 0) return 15.0;
    return 0.0;
}

double calculate_total_price(Order order) {
    double price_per_unit = get_price_for_product_code(order.product_code);
    return price_per_unit * order.quantity;
}

void parse_yaml(const char *yaml, Order *order) {
    yaml_parser_t parser;
    yaml_event_t event;
    int done = 0;

    if (!yaml_parser_initialize(&parser)) {
        fprintf(stderr, "Failed to initialize parser\n");
        exit(1);
    }

    yaml_parser_set_input_string(&parser, (unsigned char *)yaml, strlen(yaml));

    while (!done) {
        if (!yaml_parser_parse(&parser, &event)) {
            fprintf(stderr, "Error parsing YAML\n");
            exit(1);
        }

        switch (event.type) {
            case YAML_SCALAR_EVENT:
                if (strcmp((char *)event.data.scalar.value, "product_code") == 0) {
                    yaml_event_t value;
                    yaml_parser_parse(&parser, &value);
                    order->product_code = strdup((char *)value.data.scalar.value);
                } else if (strcmp((char *)event.data.scalar.value, "quantity") == 0) {
                    yaml_event_t value;
                    yaml_parser_parse(&parser, &value);
                    sscanf((char *)value.data.scalar.value, "%d", &order->quantity);
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
}

void generate_yaml_response(double total_price, char *buffer, size_t buffer_size) {
    snprintf(buffer, buffer_size, "total_price: %.2f\n", total_price);
}

int main() {
    const char *yaml_input = "product_code: A123\nquantity: 5";
    Order order;
    double total_price;
    char response[100];

    parse_yaml(yaml_input, &order);
    total_price = calculate_total_price(order);
    generate_yaml_response(total_price, response, sizeof(response));

    printf("%s", response);

    free(order.product_code);
    return 0;
}