#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <yaml.h>

typedef struct {
    char *product_code;
    int quantity;
} Order;

double get_price(const char *product_code) {
    if (strcmp(product_code, "A123") == 0) return 19.99;
    if (strcmp(product_code, "B456") == 0) return 29.99;
    if (strcmp(product_code, "C789") == 0) return 39.99;
    return 0.0;
}

char* calculate_price(const char *yaml_input) {
    Order order = {0};
    yaml_parser_t parser;
    yaml_event_t event;
    int done = 0;

    if (!yaml_parser_initialize(&parser)) {
        fprintf(stderr, "Failed to initialize parser\n");
        exit(1);
    }

    yaml_parser_set_input_string(&parser, (const unsigned char *)yaml_input, strlen(yaml_input));

    while (!done) {
        if (!yaml_parser_parse(&parser, &event)) {
            fprintf(stderr, "Error parsing YAML\n");
            exit(1);
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
                done = 1;
                break;
            default:
                break;
        }

        yaml_event_delete(&event);
    }

    double total_price = get_price(order.product_code) * order.quantity;

    char buffer[256];
    snprintf(buffer, sizeof(buffer), "total_price: %.2f\n", total_price);

    free(order.product_code);
    yaml_parser_free(&parser);

    return strdup(buffer);
}

int main() {
    const char *yaml_input = "product_code: A123\nquantity: 2";
    char *result = calculate_price(yaml_input);
    printf("%s", result);
    free(result);
    return 0;
}